#pragma once
#include "Utilities.h"

float clamp(float x, float min, float max) {

	if (x > max) {
		return max;
	}
	if (x < min) {
		return min;
	}
	else {
		return x;
	}
}

float rad2deg(float par) {
	return (par * 180 / 3.141592);
}

float deg2rad(float par) {
	return (par * 3.141592 / 180);
}

float normalize(float x, float min, float max) {
	return ((x - min) / (max - min));
}