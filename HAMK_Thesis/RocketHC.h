#pragma once
#include <SFML/Graphics.hpp>
#include "RocketController.h"
#include <string>

class RocketHC : public RocketController {
public:
	RocketHC() {}
	RocketHC(sf::Vector2f position, float angle) : RocketController (position, angle, Params::BlueNTT, Params::BlueFTT) {}
	
	virtual void controls() override;

};