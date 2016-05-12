#include "Utilities.h"
#include <sstream>

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

float CalculateDistance2(sf::Vector2f a, sf::Vector2f b) {
	return (sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2)));
}


std::vector<std::string> explode(std::string const & FullString, char Separator) {

	std::vector<std::string> result;
	std::istringstream iss(FullString);

	for (std::string token; std::getline(iss, token, Separator); ) {
		result.push_back(std::move(token));
	}

	return result;
}

float Sigmoid(float activation) {

	float response = 1.0f;
	return (1 / (1 + exp(-activation / response)));
}

float Sigmoid(float activation, float response) {
	return (1 / (1 + exp(-activation / response)));
}