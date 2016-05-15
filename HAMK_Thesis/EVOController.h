#pragma once
#include <vector>
#include "RocketController.h"
#include "Population.h"
#include "RocketNN.h"

class EVOController {


public:	

	bool BenchmarkMode = false;
	
	void run(sf::RenderWindow& window, float frametime);
	float simulate(RocketNN * Interceptor, RocketRND * EnemyRocket, NeuralNet * TheNet, float frametime, sf::RenderWindow& window);

	float CalculateDistance(RocketController * OneRocket, RocketController * OtherRocket);

	bool OutOfBounds(RocketController * Interceptor, RocketController * EnemyRocket);

};