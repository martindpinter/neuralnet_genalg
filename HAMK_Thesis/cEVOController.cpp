#include "cEVOController.h"
#include "cPopulation.h"
#include "cNeuralNet.h"
#include <SFML/Graphics.hpp>
#include <ctime>

#include "Utilities.h"

#include "cRocketNN.h"
#include "cRocketRND.h"

bool cEVOController::OutOfBounds(cRocketController * Interceptor, cRocketController * EnemyRocket) {
	// If Interceptor left the zone

	if (Interceptor -> OutOfBounds()) {
		std::cout << "Interceptor has gone out of bounds." << std::endl;
		return true;
	}
	// If EnemyRocket left the zone
	if (EnemyRocket -> OutOfBounds()) {
		std::cout << "EnemyRocket has gone out of bounds." << std::endl;
		return true;
	}
		
	return false;
	
}

float cEVOController::CalculateDistance(cRocketController * OneRocket, cRocketController * OtherRocket) {	// consider changing to points (position vectors) as parameters
	return (sqrt(pow((OtherRocket->position.x - OneRocket->position.x), 2) + pow((OtherRocket->position.y - OneRocket->position.y), 2)));

}

void cEVOController::run(sf::RenderWindow& window, float frametime) {
	//Creating 1st Generation of Random Genomes.
	
	
	
	cNeuralNet TheNet;
	
	cPopulation onePopulation;
	onePopulation.BuildRandomPopulation();

	for (int Generations = 1; Generations < 5; ++Generations) {	// for each generation

		for (int j = 0; j < cParams::PopulationSize; ++j) { // for each genome of the population
			
			cRocketNN Interceptor(cParams::posRocketNN, cParams::velRocketNN, cParams::angleRocketNN);
			cRocketRND EnemyRocket(cParams::posRocketOPP, cParams::velRocketOPP, cParams::angleRocketOPP);
			
			TheNet.feedWeights(onePopulation.Population[j].value); // feeds weights to the neurons

			onePopulation.Population[j].fitness = simulate(&Interceptor, &EnemyRocket, &TheNet, frametime, window);

			std::cout << onePopulation.Population[j].fitness << std::endl;

		}
		onePopulation.Evolve();
	}
}

float cEVOController::simulate(cRocketNN * Interceptor, cRocketRND * EnemyRocket, cNeuralNet * TheNet, float frametime, sf::RenderWindow& window) {

	Interceptor->DefineTarget(EnemyRocket);
	sf::Clock SimulationClock;
	
	// for each frame

	bool CollisionDetection = false;
	float ClosestDistance = sqrt(pow(cParams::WindowHeight, 2) + pow(cParams::WindowWidth, 2));

	while (!OutOfBounds(Interceptor, EnemyRocket) && CollisionDetection == false) {

		Interceptor->SetNNControls(TheNet);
		Interceptor->update(frametime);
		EnemyRocket->update(frametime);

		//std::cout << "Interceptor ::  X [" << Interceptor->position.x << "]   Y [" << Interceptor->position.y << "]" << std::endl;
		//std::cout << "Interceptor's Angle [" << rad2deg(Interceptor->angle) << "] " << std::endl;
		
		
		CollisionDetection = Interceptor->collision(EnemyRocket);
		float CurrentDistance = CalculateDistance(Interceptor, EnemyRocket);

		if (CurrentDistance < ClosestDistance) {
			ClosestDistance = CurrentDistance;
		}

		if (BenchmarkMode == false) {
			window.clear(sf::Color::Black);
			Interceptor->draw(window);
			EnemyRocket->draw(window);
			window.display();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
				return 0;
			}
		}

	}

	float SimulationTime = SimulationClock.restart().asSeconds();

	return (CollisionDetection * SimulationTime + !CollisionDetection * ClosestDistance) / (SimulationTime + (!CollisionDetection * 100));

}