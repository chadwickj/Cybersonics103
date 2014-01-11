#ifndef CONSTANTS_H
#define CONSTANTS_H

// PNEUMATICS

static const int COMPRESSOR_RELAY_CHAN = 1;
static const int PRESSURE_SWITCH_CHAN = 14;

//LIGHT
static const int LED_DIGITAL_OUTPUT = 2;

// MOTORS

static const int LEFT_DRIVE_PWM = 1;
static const int RIGHT_DRIVE_PWM = 2;

static const int PICKUP_PWM = 4;

static const int SHOOTER_BAG_PWM = 5;
static const int SHOOTER_775_PWM = 8;

//CLIMBER MOTORS

static const int CLIMB_WINDOW = 7;
static const int CLIMB_CIM = 10;

// CONTROLS

static const int LEFT_JOYSTICK_PORT = 1;
static const int RIGHT_JOYSTICK_PORT = 2;
static const int SHOOTER_JOYSTICK_PORT = 3;
static const int CLIMBER_JOYSTICK_PORT = 4;

//STRING POT

static const int TILT_POT_CHAN = 3;
static const int MAST_POT_CHAN = 4;

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
