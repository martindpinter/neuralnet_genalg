#include <iostream>
#include <SFML/Graphics.hpp>

#include "RocketHC.h"
#include "Utilities.h"
#include "Params.h"

void RocketHC::controlls() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		//throttle
		accelerate(0.33f);	//	a trukk az, hogy itt is meg kell szorozni, 1/3sec alatt gyorsul fullra (0.33f)
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		//angular_accelerate(-0.66f * frametime);
		angular_accelerate(-1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		//angular_accelerate(0.66f * frametime);	//masfel sec alatt gyorsul 100ra
		angular_accelerate(1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		accelerate(-0.33f);
	}
}

void RocketHC::reset() {
	position = Params::posRocketNN;
	velocity = Params::velRocketNN;
	angle = Params::angleRocketNN;
}
