#pragma once
#include "RocketNN.h"

class Interceptor : public RocketNN {
public:
	Interceptor() {}
	Interceptor(sf::Vector2f position, float angle) : RocketNN(position, angle) {}

	virtual std::vector<float> getNNinputs() override;

	void reset();

	// how to implement fitness calculation method difference here as virtual override?
	// think about it later!
};