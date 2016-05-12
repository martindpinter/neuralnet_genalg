#pragma once
#include "Manager.h"


class GraphicalRun : public Manager {
public:
	GraphicalRun() : 
		Window(sf::VideoMode(Params::WindowWidth, Params::WindowHeight), "Martin Pinter - HAMK Thesis", sf::Style::None) {}
	
	sf::RenderWindow Window;

	virtual float Simulate() override;
	void HandleUserInput();

	float fps;
	float fpsLimit;

	bool pressedKeys[sf::Keyboard::KeyCount] = { false };

};
