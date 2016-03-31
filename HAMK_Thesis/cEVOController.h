#pragma once
#include <vector>
#include "cRocketController.h"
#include "cPopulation.h"
#include "cRocketNN.h"

class cEVOController {


public:	

	bool BenchmarkMode = false;
	
	void run(sf::RenderWindow& window, float frametime);
	float simulate(cRocketNN * Interceptor, cRocketRND * EnemyRocket, cNeuralNet * TheNet, float frametime, sf::RenderWindow& window);

	float CalculateDistance(cRocketController * OneRocket, cRocketController * OtherRocket);

	bool OutOfBounds(cRocketController * Interceptor, cRocketController * EnemyRocket);

};