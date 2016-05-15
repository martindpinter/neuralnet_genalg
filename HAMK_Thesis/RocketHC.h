#pragma once
#include <SFML/Graphics.hpp>
#include "RocketController.h"
#include <string>

class RocketHC : public RocketController {
public:
	RocketHC() {}
	RocketHC(sf::Vector2f position, float angle) : RocketController (position, angle, "../images/resized_by5/rocket.png", "../images/resized_by5/rocket_throttle.png") {}
	
	virtual void controls() override;
	virtual void CollisionDetection() override;
	virtual void reset() override;

};