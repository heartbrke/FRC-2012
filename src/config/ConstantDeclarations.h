/**
 * @author Eric Caldwell
 *
 * This file is read by Constants and contains the variables and default values that will be stored as member
 * variables in Constants. Use it by including it in the macro definition of the functions used below.
 */

// Motors

DECLARE_DOUBLE(leftDrivePwmA, 5)
DECLARE_DOUBLE(leftDrivePwmB, 4)
DECLARE_DOUBLE(rightDrivePwmA, 6)
DECLARE_DOUBLE(rightDrivePwmB, 7)
DECLARE_DOUBLE(intakePwm1, 2)
DECLARE_DOUBLE(intakePwm2, 1)
DECLARE_DOUBLE(intakePwm3, 10)
DECLARE_DOUBLE(conveyorPwm, 9)
DECLARE_DOUBLE(leftShooterPwm, 3)
DECLARE_DOUBLE(rightShooterPwm, 8)

// Analog sensors
DECLARE_DOUBLE(gyroPort, 1)
DECLARE_DOUBLE(poofMeterPort, 4)
DECLARE_DOUBLE(ballRangerPort, 2)
DECLARE_DOUBLE(conveyorBallSensorPort, 3)

// Digital sensors
DECLARE_DOUBLE(bumpSensorPort, 1)
DECLARE_DOUBLE(leftEncoderPortA, 2)
DECLARE_DOUBLE(leftEncoderPortB, 3)
DECLARE_DOUBLE(rightEncoderPortA, 4)
DECLARE_DOUBLE(rightEncoderPortB, 5)
DECLARE_DOUBLE(shooterEncoderPortA, 6)
DECLARE_DOUBLE(shooterEncoderPortB, 7)

// Pneumatics
DECLARE_DOUBLE(compressorPressureSwitchPort, 14)
DECLARE_DOUBLE(compressorRelayPort, 8)
DECLARE_DOUBLE(pizzaWheelSolenoidUpPort, 1)
DECLARE_DOUBLE(pizzaWheelSolenoidDownPort, 4)
DECLARE_DOUBLE(hoodSolenoidPort, 6)
DECLARE_DOUBLE(intakeSolenoidUpPort, 5)
DECLARE_DOUBLE(intakeSolenoidDownPort, 7)
DECLARE_DOUBLE(brakeSolenoidOnPort, 2)
DECLARE_DOUBLE(brakeSolenoidOffPort, 3)
DECLARE_DOUBLE(shiftSolenoidPort, 8)

// Vision
DECLARE_DOUBLE(thresholdRMin, 0)
DECLARE_DOUBLE(thresholdRMax, 50)
DECLARE_DOUBLE(thresholdGMin, 0)
DECLARE_DOUBLE(thresholdGMax, 50)
DECLARE_DOUBLE(thresholdBMin, 80)
DECLARE_DOUBLE(thresholdBMax, 255)

// Driver controls
DECLARE_DOUBLE(leftJoystickPort, 1)
DECLARE_DOUBLE(rightJoystickPort, 2)

// Operator controls
DECLARE_DOUBLE(operatorControlPort, 3)
DECLARE_DOUBLE(intakeUpPort, 4)
DECLARE_DOUBLE(intakeDownPort, 12)
DECLARE_DOUBLE(autonSelectPort, 11)
DECLARE_DOUBLE(unjamPort, 10)
DECLARE_DOUBLE(shootPort, 9)
DECLARE_DOUBLE(autoShootPort, 8)
DECLARE_DOUBLE(intakePort, 7)
DECLARE_DOUBLE(increasePort, 6)
DECLARE_DOUBLE(decreasePort, 5)
DECLARE_DOUBLE(keyFarPort, 4)
DECLARE_DOUBLE(keyClosePort, 3)
DECLARE_DOUBLE(farFenderPort, 2)
DECLARE_DOUBLE(fenderPort, 1)
DECLARE_DOUBLE(shooterOnPort, 3)

// Left joystick
DECLARE_DOUBLE(autoAlignPort, 2);
DECLARE_DOUBLE(highGearPort, 3);

// Right joystick
DECLARE_DOUBLE(quickTurnPort, 2);
DECLARE_DOUBLE(pizzaSwitchPort, 3);

// Linearization
DECLARE_DOUBLE(linearCoeffA, 4.5504)
DECLARE_DOUBLE(linearCoeffB, -5.9762)
DECLARE_DOUBLE(linearCoeffC, 2.5895)
DECLARE_DOUBLE(linearCoeffD, -0.0869)
DECLARE_DOUBLE(linearCoeffE, 0.0913)
DECLARE_DOUBLE(shooterCoeffA, 4.7658)
DECLARE_DOUBLE(shooterCoeffB, -5.8827)
DECLARE_DOUBLE(shooterCoeffC, 1.8275)
DECLARE_DOUBLE(shooterCoeffD, 0.2894)
DECLARE_DOUBLE(conveyorCoeffA, 0.5021)
DECLARE_DOUBLE(conveyorCoeffB, 0.16)
DECLARE_DOUBLE(conveyorCoeffC, 0.3228)
DECLARE_DOUBLE(conveyorCoeffD, 1.1347)

// Camera relations
DECLARE_DOUBLE(distanceCoeffA, 244.56)
DECLARE_DOUBLE(distanceCoeffB, 5)
DECLARE_DOUBLE(distanceCoeffC, 1.4524)

// Drive tuning
DECLARE_DOUBLE(turnSensLow, 1.1)
DECLARE_DOUBLE(turnSensHigh, 1.4)

// Shooter
DECLARE_DOUBLE(shooterFenderSpeed, 38)
DECLARE_DOUBLE(shooterFarFenderSpeed, 46)
DECLARE_DOUBLE(shooterKeyCloseSpeed, 48)
DECLARE_DOUBLE(shooterKeyFarSpeed, 53)
DECLARE_DOUBLE(shooterSpeedIncrement, 0.5)

// PID constants
DECLARE_DOUBLE(driveKP, 0.12)
DECLARE_DOUBLE(driveKI, 0.0)
DECLARE_DOUBLE(driveKD, 1.2)
DECLARE_DOUBLE(driveVelKP, 0.0006)
DECLARE_DOUBLE(driveVelKI, 0.0000)
DECLARE_DOUBLE(driveVelKD, 0.0005)
DECLARE_DOUBLE(baseLockKP, 1.5)
DECLARE_DOUBLE(baseLockKI, 0.01)
DECLARE_DOUBLE(baseLockKD, 0)
DECLARE_DOUBLE(shooterKP, 0.600)
DECLARE_DOUBLE(shooterKI, 0.700)
DECLARE_DOUBLE(shooterKD, -0.950)
DECLARE_DOUBLE(turnKP, 0.074)
DECLARE_DOUBLE(turnKI, 0.000)
DECLARE_DOUBLE(turnKD, 0.550)
DECLARE_DOUBLE(breakStaticOffset, 0.4)
DECLARE_DOUBLE(autoCameraAlignKP, 0.074)
DECLARE_DOUBLE(autoCameraAlignKI, 0.0)
DECLARE_DOUBLE(autoCameraAlignKD, .55)
DECLARE_DOUBLE(straightDriveGain, 0.1)

// Automomous
DECLARE_DOUBLE(autoShootKeyVel, 51)
DECLARE_DOUBLE(autoAlignThreshold, 1.0)
