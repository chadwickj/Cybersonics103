#ifndef CONSTANTS_H
#define CONSTANTS_H

// MOTORS

static const int LEFT_DRIVE_PWM = 1;
static const int RIGHT_DRIVE_PWM = 2;

// CONTROLS

static const int LEFT_JOYSTICK_PORT = 1;
static const int RIGHT_JOYSTICK_PORT = 2;

// SENSORS

static const int LEFT_ENCODER_A = 11;
static const int LEFT_ENCODER_B = 12;
static const int RIGHT_ENCODER_A = 13;
static const int RIGHT_ENCODER_B = 14;

// Encoders are geared at a 1:1 ratio.
// TODO: Configuration for left and right sides of drivetrain.
static const double TIRE_CIRCUMFERENCE = 27.75; 	// in inches
static const double COUNTS_PER_REVOLUTION = 128.0;
static const double INCHES_PER_COUNT = TIRE_CIRCUMFERENCE / COUNTS_PER_REVOLUTION;

#endif
