#include "cRocketHC.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include <iostream>

void cRocketHC::controlls(float frametime) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		//throttle
		accelerate(0.33f * frametime);	//	a trukk az, hogy itt is meg kell szorozni, 1/3sec alatt gyorsul fullra (0.33f)
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		//angular_accelerate(-0.66f * frametime);
		angular_accelerate(-1.0f * frametime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		//angular_accelerate(0.66f * frametime);	//masfel sec alatt gyorsul 100ra
		angular_accelerate(1.0f * frametime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		accelerate(-0.33f * frametime);
	}
}
