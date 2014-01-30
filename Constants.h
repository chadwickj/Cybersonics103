#ifndef CONSTANTS_H
#define CONSTANTS_H

// PNEUMATICS

static const int COMPRESSOR_RELAY_CHAN = 1;
static const int PRESSURE_SWITCH_CHAN = 14;

// SOLENOIDS

static const int LAUNCHER_FIRE_SOLENOID = ;
static const int LAUNCHER_RESET_SOLENOID = ;
static const int LAUNCHER_TRIGGER_SOLENOID = ;

static const int SHIFT_UP_SOLENOID = ;
static const int SHIFT_DOWN_SOLENOID = ;

static const int BRAKES_ON_SOLENOID = ;
static const int BRAKES_OFF_SOLENOID = ;

// LIGHT
static const int LED_RELAY_CHAN = 2;

// MOTORS

static const int LEFT_DRIVE_PWM = 1;
static const int RIGHT_DRIVE_PWM = 2;

// PICKUP

static const int PICKUP_MOTOR = ;
static const int PICKUP_ARM_MOTOR = ;

// SHOOTER

static const int SHOOTER_MOTOR = ;

// ANALOG CHANNELS

static const int SHOOTER_MOTOR_POT = ;

// CONTROLS

static const int LEFT_JOYSTICK_PORT = 1;
static const int RIGHT_JOYSTICK_PORT = 2;
static const int OPERATOR_JOYSTICK_PORT = ;

static const int SHOOTER_BUTTON = ;

static const int BRAKES_BUTTON = ;
static const int SHIFTER_BUTTON = ;

// SENSORS

static const int LEFT_ENCODER_A = 1;
static const int LEFT_ENCODER_B = 2;
static const int RIGHT_ENCODER_A = 3;
static const int RIGHT_ENCODER_B = 4;

static const int GYRO_CHANNEL = 1;
static const float GYRO_SENSITIVITY = 0.007; // 7 mV/deg/sec

static const int ULTRASONIC_CHANNEL = 2;

// ENCODER PID
static const float LEFT_ENCODER_P = 0.015;
static const float LEFT_ENCODER_I = 0.0;
static const float LEFT_ENCODER_D = 0.0;

static const float RIGHT_ENCODER_P = 0.013;
static const float RIGHT_ENCODER_I = 0.0;
static const float RIGHT_ENCODER_D = 0.0;

// GYRO PID
static const float GYRO_P = 0.013022;
static const float GYRO_I = 0.0;
static const float GYRO_D = 0.002116;

// DRIVE STRAIGHT
static const float DRIVE_STRAIGHT_P = 0.0002;

// Encoders are geared at a 1:1 ratio.
// TODO: Configuration for left and right sides of drivetrain.
static const double TIRE_CIRCUMFERENCE = 27.75; 	// in inches
static const double COUNTS_PER_REVOLUTION = 128.0;
static const double INCHES_PER_COUNT = TIRE_CIRCUMFERENCE / COUNTS_PER_REVOLUTION;

#endif
