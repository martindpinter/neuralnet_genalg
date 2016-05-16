#pragma once
#include "RocketController.h"

class Bandit : public RocketController {
public:

	Bandit() {}
	Bandit(sf::Vector2f position, float angle) : RocketController(position, angle, Params::RedNTT, Params::RedFTT) {}

	void reset(int seed);
	virtual void controls() override;

	virtual void update() override;
};