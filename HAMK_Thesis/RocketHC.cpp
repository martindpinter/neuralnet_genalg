#include <iostream>
#include <SFML/Graphics.hpp>

#include "RocketHC.h"
#include "Utilities.h"
#include "Params.h"

void RocketHC::controls() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		accelerate(0.01f);
	}
	else accelerate(-0.006f);
	//else throttle = 0.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (angular_throttle > 0)
			angular_accelerate(-0.03f);
		else
			angular_accelerate(-0.01f);
		
		
		//angular_accelerate(-0.01f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (angular_throttle < 0)
			angular_accelerate(0.03f);
		else
			angular_accelerate(0.01f);
	}
	else {
		angular_accelerate((-1 * angular_throttle) / 30);
		//angular_throttle = 0;
	}
		


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		accelerate(-0.33f);
	}
}

void RocketHC::CollisionDetection() {
	Collided = false;
}

void RocketHC::reset() {
	position = Params::posRocketHC;
	velocity = Params::nullvec;
	angle = Params::angleRocketHC;
	throttle = 0.0f;
	angular_throttle = 0.0f;
	angular_velocity = 0.0f;
	rotationalSum = 0.0f;
}
