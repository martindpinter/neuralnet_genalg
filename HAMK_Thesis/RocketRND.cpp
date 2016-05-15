#include "RocketRND.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include "Params.h"
#include <random>

void RocketRND::controls() {
	bool flipflop = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad5)) {
		// start random sequence
		flipflop = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad0)) {
		flipflop = false;
	}

	//azert menjen egyenesen elore
	if (flipflop == true) {
		int rnd_action = rand() % 4 + 1;

		switch (rnd_action) {
		case 1: accelerate(0.75f);	// UP
			break;
		case 2: accelerate(-0.75f);	// DOWN
			break;
		case 3: angular_accelerate(-1.0f);	// LEFT
			break;
		case 4: angular_accelerate(1.0f);	// RIGHT
			break;
		}
	}
}

void RocketRND::reset() {
	position = Params::posRocketOPP;
	velocity = Params::nullvec;
	angle = Params::angleRocketOPP;
	throttle = 0.0f;
	angular_throttle = 0.0f;
	angular_velocity = 0.0f;
	rotationalSum = 0.0f;
}

