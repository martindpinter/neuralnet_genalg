#pragma once
#include <SFML/Graphics.hpp>
#include "cRocketController.h"

//	***	This class describes randomly controlled rockets


class cRocketRND : public cRocketController {
public:

	cRocketRND(sf::Vector2f position, sf::Vector2f velocity, float angle) 
		: cRocketController(position, velocity, angle, "../images/resized_by5/BlueRocket.png", "../images/resized_by5/BlueRocket_throttle.png") {}

	virtual void controlls(float frametime) override;	//virtual!!!

};