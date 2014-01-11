#ifndef HELPER_H
#define HELPER_H

#include "Constants.h"
#include <cmath>

double encoderCountToInches(int encoderCount) {
	return encoderCount * INCHES_PER_COUNT;
}

double inchesToEncoderCounts(double inches) {
	return inches / INCHES_PER_COUNT;
}

#endif
