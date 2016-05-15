#pragma once
#include "RocketNN.h"

class Bandit : public RocketNN {
public:

	Bandit() {}
	Bandit(sf::Vector2f position, float angle) : RocketNN(position, angle) {}

	virtual std::vector<float> getNNinputs() override;

	virtual void reset() override;

};