#include "cRocketController.h"
#include "cRocketHC.h"
#include "cRocketRND.h"
#include "cRocketNN.h"
#include "cNeuralNet.h"
#include "cParams.h"
#include "cPopulation.h"

#include "cEVOController.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#define PI 3.141592;

//bool collision(cRocketHC& oneRocket, cRocketRND& otherRocket);


int main() {
	
	srand(time(nullptr));

	sf::Clock frameclock;

	sf::RenderWindow window(sf::VideoMode(cParams::WindowWidth, cParams::WindowHeight), "Martin Pinter - HAMK Thesis");
	window.setFramerateLimit(cParams::Framerate);

	// tha real deal
	cEVOController nature;

	while (window.isOpen()) {
		//Frametime counting	
		float frametime = frameclock.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) { window.close(); }
		}

		nature.run(window, frametime);		

		window.display();		//end the current frame

	}
	return 0;
}

