#include <iostream>
#include <SFML/Graphics.hpp>

#include "RocketHC.h"
#include "Utilities.h"
#include "Params.h"

void RocketHC::controlls() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		//throttle
		accelerate(0.9f);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		angular_accelerate(-0.9f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		angular_accelerate(0.9f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		accelerate(-0.33f);
	}
}

void RocketHC::reset() {
	position = Params::posRocketHC;
	velocity = Params::velRocketHC;
	angle = Params::angleRocketHC;
	throttle = 0.0f;
	angular_throttle = 0.0f;
	angular_velocity = 0.0f;
	rotationalSum = 0.0f;
}
