#pragma once
#include <SFML/Graphics.hpp>
#include "RocketController.h"

//	***	This class describes randomly controlled rockets


class RocketRND : public RocketController {
public:
	RocketRND() {}
	RocketRND(sf::Vector2f position, float angle) 
		: RocketController(position, angle, "../images/resized_by5/BlueRocket.png", "../images/resized_by5/BlueRocket_throttle.png") {}

	virtual void controls() override;

	virtual void reset() override;

};