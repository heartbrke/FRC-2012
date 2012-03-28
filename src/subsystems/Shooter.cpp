#include "subsystems/Shooter.h"

#include <cmath>
#include "utils.hpp"

#include "util/PidTuner.h"

Shooter::Shooter(Victor* conveyorMotor, Victor* leftShooterMotor, Victor* rightShooterMotor,
                Encoder* shooterEncoder, Solenoid* hoodSolenoid, AnalogChannel* ballSensor,
                AnalogChannel* poofMeter, AnalogChannel* ballRanger) {
  constants_ = Constants::GetInstance();
  conveyorMotor_ = conveyorMotor;
  leftShooterMotor_ = leftShooterMotor;
  rightShooterMotor_ = rightShooterMotor;
  shooterEncoder_ = shooterEncoder;
  hoodSolenoid_ = hoodSolenoid;
  prevPos_ = 0;
  ballSensor_ = ballSensor;
  targetVelocity_ = 0.0;
  velocity_ = 0.0;
  timer_ = new Timer();
  timer_->Reset();
  timer_->Start();
  pid_ = new Pid(&constants_->shooterKP, &constants_->shooterKI, &constants_->shooterKD);
  for (int i = 0; i < FILTER_SIZE; i++) {
    velocityFilter_[i] = 0;
  }
  filterIndex_ = 0;
  outputValue_ = 0;
  for (int i = 0; i < OUTPUT_FILTER_SIZE; i++) {
    outputFilter_[i] = 0;
  }
  outputFilterIndex_ = 0;
  poofMeter_ = poofMeter;
  poofCorrectionFactor_ = 1.0;
  prevBallSensor_ = false;
  ballRanger_ = ballRanger;
  filter_ = DaisyFilter::SinglePoleIIRFilter(0.5f);
  pidGoal_ = 0.0;
  atTarget_ = false;
  
  y_ = init_matrix(1,1);
    r_ = init_matrix(2,1);
    flash_matrix(y_, 0.0);
    flash_matrix(r_, 0.0, 0.0);
    ssc_ = new ss_controller(1, 1, 2, ss_controller::SHOOTER);
    ssc_->reset();
    
}

void Shooter::SetLinearPower(double pwm) {
  SetPower(Linearize(pwm));
}

void Shooter::SetTargetVelocity(double velocity) {
  targetVelocity_ = velocity;
  pid_->ResetError();
  outputValue_ = 0;
  if (velocity > 40) {
    SetHoodUp(true);
  } else if (velocity > 0) {
    SetHoodUp(false);
  }

}

bool Shooter::PIDUpdate() {
  double dt = timer_->Get();
  timer_->Reset();
  
  
	  //int currEncoderPos = shooterEncoder_->Get();
  double currEncoderPos = shooterEncoder_->GetRaw() / 128.0 * 2 * 3.1415926;
  double velocity_goal = 2 * 3.1415926 * targetVelocity_;
  double instantVelocity = ((currEncoderPos - prevPos_) /  (1.0/50.0)); // (2 * 3.1415926);
  //printf(" v: %f pow: %f dt: %f\n\n", instantVelocity, ssc_.U->data[0], dt);
  flash_matrix(y_, (double)currEncoderPos);
  const double velocity_weight_scalar = 0.35;
  //const double max_reference = (U_max[0] - velocity_weight_scalar * (velocity_goal - X_hat[1]) * K[1]) / K[0] + X_hat[0];
  //const double min_reference = (U_min[0] - velocity_weight_scalar * (velocity_goal - X_hat[1]) * K[1]) / K[0] + X_hat[0];
  double u_min = ssc_->U_min->data[0];
  double u_max = ssc_->U_max->data[0];
  double x_hat1 = ssc_->X_hat->data[1];
  double k1 = ssc_->K->data[1];
  double k0 = ssc_->K->data[0];
  double x_hat0 = ssc_->X_hat->data[0];
  const double max_reference = (u_max - velocity_weight_scalar * (velocity_goal - x_hat1) * k1) / k0 + x_hat0;
  const double min_reference = (u_min - velocity_weight_scalar * (velocity_goal - x_hat1) * k1) / k0 + x_hat0;
  //pidGoal_ = max(min(pidGoal_, max_reference), min_reference);
  double minimum = (pidGoal_ < max_reference) ? pidGoal_ : max_reference;
  pidGoal_ = (minimum > min_reference) ? minimum : min_reference;
  //printf("min %f max %f r %f\n", min_reference, max_reference, pidGoal_);
  flash_matrix(r_, pidGoal_, velocity_goal);
  pidGoal_ += ((1.0/50.0) * velocity_goal);
  ssc_->update(r_, y_);
  //printf("r: %f %f\n", r_->data[0], r_->data[1]);
  //printf("y: %f\n", y_->data[0]);
  //printf("u: %f\n", ssc_.U->data[0]);
  if (velocity_goal < 1.0) {
	  //printf("minning out\n");
	  SetLinearPower(0.0);
	  pidGoal_ = currEncoderPos;
  } else {
	  //printf("Power: %f\n", ssc_.U->data[0] / 12.0);
	  SetLinearPower(ssc_->U->data[0] / 12.0);
  }

  //PidTuner::PushData(x_hat1, instantVelocity, dt*50*100);
  //PidTuner::PushData(x_hat0, x_hat1, x_hat1);
  

  //double instantVelocity = ((currEncoderPos - prevPos_) /  (1.0/50.0)); // (2 * 3.1415926);
 // printf(" v: %f pow: %f dt: %f\n\n", instantVelocity, ssc_.U->data[0], dt);
  

  instantVelocity =  instantVelocity / (2 * 3.1415926);
  velocity_ = UpdateFilter(instantVelocity);
 // printf("t: %f , v: %f\n", targetVelocity_, velocity_);

  prevPos_ = currEncoderPos;
  DriverStationLCD* lcd_ = DriverStationLCD::GetInstance();
  lcd_->PrintfLine(DriverStationLCD::kUser_Line4, "x0: %f", x_hat0);
  lcd_->PrintfLine(DriverStationLCD::kUser_Line5, "x1: %f", x_hat1);
  lcd_->PrintfLine(DriverStationLCD::kUser_Line6, "v: %f g: %f ", velocity_, velocity_goal);
  lcd_->UpdateLCD();

  
  atTarget_ = fabs(velocity_ - targetVelocity_) < VELOCITY_THRESHOLD;
  PidTuner::GetInstance()->PushData(targetVelocity_,velocity_, 0);
  //SetLinearPower(.8);
  //return false;
  return atTarget_;
}

void Shooter::SetLinearConveyorPower(double pwm) {
  conveyorMotor_->Set(pwm);
}

bool Shooter::AtTargetVelocity() {
	return atTarget_;
}

void Shooter::SetHoodUp(bool up) {
  hoodSolenoid_->Set(up);
}

double Shooter::UpdateFilter(double value) {
  velocityFilter_[filterIndex_] = value;
  filterIndex_++;
  if (filterIndex_ == FILTER_SIZE) {
    filterIndex_ = 0;
  }
  double sum = 0;
  for (int i = 0; i < FILTER_SIZE; i++) {
    sum += velocityFilter_[i];
  }
  return sum / (double)FILTER_SIZE;
}

double Shooter::UpdateOutputFilter(double value) {
  outputFilter_[outputFilterIndex_] = value;
  outputFilterIndex_++;
  if (outputFilterIndex_ == OUTPUT_FILTER_SIZE) {
    outputFilterIndex_ = 0;
  }
  double sum = 0;
  for (int i = 0; i < OUTPUT_FILTER_SIZE; i++) {
    sum += outputFilter_[i];
  }
  return sum / (double)OUTPUT_FILTER_SIZE;
}

double Shooter::GetVelocity() {
  return velocity_;
}

void Shooter::SetPower(double power) {
  // The shooter should only ever spin in one direction.
  if (power < 0 || targetVelocity_ == 0) {
    power = 0;
  }
  leftShooterMotor_->Set(PwmLimit(-power));
  rightShooterMotor_->Set(PwmLimit(-power));
}

double Shooter::Linearize(double x) {
  if (x >= 0.0) {
    return constants_->shooterCoeffA * pow(x, 4) + constants_->shooterCoeffB * pow(x, 3) +
        constants_->shooterCoeffC * pow(x, 2) + constants_->shooterCoeffD * x;
  } else {
    // Rotate the linearization function by 180.0 degrees to handle negative input.
    return -Linearize(-x);
  }
}

void Shooter::Reset() {
  atTarget_ = false;
  for (int i = 0; i < FILTER_SIZE; i++) {
	velocityFilter_[i] = 0;
  }
  flash_matrix(y_, 0.0);
  flash_matrix(r_, 0.0, 0.0);
  ssc_->reset();
}

double Shooter::ConveyorLinearize(double x) {
  if (fabs(x) < 0.01 ) {
    return 0;
  } else if (x > 0) {
    return constants_->conveyorCoeffA * pow(x, 3) + constants_->conveyorCoeffB * pow(x, 2) +
        constants_->conveyorCoeffC * x + constants_->conveyorCoeffD;
  } else {
    // Rotate the linearization function by 180.0 degrees to handle negative input.
    return -Linearize(-x);
  }
}

double Shooter::GetBallRange() {
	return ballRanger_->GetValue();
}
