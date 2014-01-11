#ifndef HELPER_H
#define HELPER_H

#include "Constants.h"
#include <cmath>

static double encoderCountToInches(int encoderCount) {
	return encoderCount * INCHES_PER_COUNT;
}

/*
static double inchesToEncoderCounts(double inches) {
	return inches / INCHES_PER_COUNT;
}*/

#endif
