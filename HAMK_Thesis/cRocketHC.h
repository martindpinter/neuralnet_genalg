#pragma once
#include <SFML/Graphics.hpp>
#include "cRocketController.h"
#include <string>

class cRocketHC : public cRocketController {
public:
	cRocketHC(sf::Vector2f position, sf::Vector2f velocity, float angle) : cRocketController (position, velocity, angle, "../images/resized_by5/rocket.png", "../images/resized_by5/rocket_throttle.png") {}
	
	virtual void controlls(float frametime) override;	//virtual!!!

};