#pragma once
#include "Manager.h"

class GraphicalRun : public Manager {
public:
	GraphicalRun() : 
		Window(sf::VideoMode(Params::WindowWidth, Params::WindowHeight), "Graphical Simulation :: Martin Pinter - HAMK Thesis", sf::Style::None), SpeedFactor(1.0f) {}
	
	sf::RenderWindow Window;

	virtual bool Simulate() override;
	void HandleUserInput();

	float SpeedFactor;

	bool abort = false;

	bool pressedKeys[sf::Keyboard::KeyCount] = { false };

};
