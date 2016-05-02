#include "cRocketRND.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include <random>

void cRocketRND::controlls(float frametime) {
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
		case 1: accelerate(0.75f * frametime);	// UP
			break;
		case 2: accelerate(-0.75f * frametime);	// DOWN
			break;
		case 3: angular_accelerate(-1.0f * frametime);	// LEFT
			break;
		case 4: angular_accelerate(1.0f * frametime);	// RIGHT
			break;
		}
	}
}

