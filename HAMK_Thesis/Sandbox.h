#pragma once
#include <SFML/Graphics.hpp>
#include "Params.h"
#include "RocketHC.h"
#include "RocketRND.h"

class Sandbox {
public:
	Sandbox() : Window(sf::VideoMode(Params::WindowWidth, Params::WindowHeight), "Sandbox Mode", sf::Style::None) {
		UserRocket = RocketHC(Params::posRocketHC, Params::angleRocketHC);
	
	}

	sf::RenderWindow Window;

	void HandleUserInput();

	void Run();

	float fps;
	float fpsLimit;

	RocketHC UserRocket;
	//RocketRND Bandit;

	bool pressedKeys[sf::Keyboard::KeyCount] = { false };
};