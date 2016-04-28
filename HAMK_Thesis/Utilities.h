#pragma once
#include <cstdlib>


float clamp(float x, float min, float max);
float rad2deg(float);
float deg2rad(float);
float normalize(float x, float min, float max);
float RescaleAtan2(float par);



struct SPoint {
	float x, y;

	SPoint() {}
	SPoint(float a, float b) : x(a), y(b) {}
};





//	RANDOM NUMBER FUNCTIONS		FROM AIJUNKIE
//	...

inline int randInt(int x, int y) {
	return rand() % (y - x + 1) + x;
}

inline float randfloat() {
	return (rand()) / (RAND_MAX + 1.0);
}

inline float randfloat(float x, float y) {
	float RandBase = ((float)rand() / (float)RAND_MAX);	
	float range = y - x;
	float random = RandBase * range;
	return x + random;
}

inline bool randBool() {
	if (randInt(0, 1)) return true;
	else return false;
}

inline float randClamped()	{ // -1 < n < 1 
	return randfloat() - randfloat();
}

//	...;

