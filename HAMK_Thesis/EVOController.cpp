#include "EVOController.h"
#include "Population.h"
#include "NeuralNet.h"
#include <SFML/Graphics.hpp>
#include <ctime>

#include "Utilities.h"

#include "RocketNN.h"
#include "RocketRND.h"

bool EVOController::OutOfBounds(RocketController * Interceptor, RocketController * EnemyRocket) {
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

float EVOController::CalculateDistance(RocketController * OneRocket, RocketController * OtherRocket) {

	return (sqrt(pow((OtherRocket->position.x - OneRocket->position.x), 2) + pow((OtherRocket->position.y - OneRocket->position.y), 2)));
}

void EVOController::run(sf::RenderWindow& window, float frametime) {
	//Creating 1st Generation of Random Genomes.
	
	NeuralNet TheNet;
	
	Population onePopulation;
	onePopulation.BuildRandomPopulation();


	for (int Generations = 1; Generations < 5; ++Generations) {	// for each generation

		for (int j = 0; j < Params::PopulationSize; ++j) { // for each genome of the population
			
			RocketNN Interceptor(Params::posRocketNN, Params::velRocketNN, Params::angleRocketNN);
			RocketRND EnemyRocket(Params::posRocketOPP, Params::velRocketOPP, Params::angleRocketOPP);
			
			TheNet.feedWeights(onePopulation.ThePopulation[j].value); // feeds weights to the neurons

			onePopulation.ThePopulation[j].fitness = simulate(&Interceptor, &EnemyRocket, &TheNet, frametime, window);

			std::cout << onePopulation.ThePopulation[j].fitness << std::endl;

		}
		onePopulation.Evolve();
	}
}

float EVOController::simulate(RocketNN * Interceptor, RocketRND * EnemyRocket, NeuralNet * TheNet, float frametime, sf::RenderWindow& window) {

	Interceptor->DefineTarget(EnemyRocket);
	sf::Clock SimulationClock;
	
	// for each frame

	bool CollisionDetection = false;
	float ClosestDistance = sqrt(pow(Params::WindowHeight, 2) + pow(Params::WindowWidth, 2));

	while (!OutOfBounds(Interceptor, EnemyRocket) && CollisionDetection == false) {

		Interceptor->SetNNControls(TheNet);
		
		Interceptor->update(frametime);
		
		EnemyRocket->update(frametime);		
		
		CollisionDetection = Interceptor->collision(EnemyRocket);
		
		float CurrentDistance = CalculateDistance(Interceptor, EnemyRocket);


		if (CurrentDistance < ClosestDistance) {
			ClosestDistance = CurrentDistance;
		}

		if (Params::GraphicalSimulation == true) {
			
			window.clear(sf::Color::Black);
			
			Interceptor->draw(window);
			
			EnemyRocket->draw(window);
			
			window.display();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
				return 0.0f;
			}
		}

	}

	float SimulationTime = SimulationClock.restart().asSeconds();

	return (CollisionDetection * (1 - SimulationTime / 10) + !CollisionDetection * (1 / ClosestDistance * SimulationTime));

}