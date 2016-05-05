#include "PerformanceRun.h"

float PerformanceRun::Simulate() {
	
	sf::Clock SimulationClock;

	bool CollisionDetection = false;

	float ClosestDistance = sqrt(pow(Params::WindowHeight, 2) + pow(Params::WindowWidth, 2));

	int NrOfUpdates = 0;

	while (!CollisionDetection && !OutOfBounds()) {

		Interceptor.SetNNControls(&TheNet);
		// Bandit's controls should be given here instead of static movement


		Interceptor.update();
		Bandit.update();
		NrOfUpdates++;


		CollisionDetection = Interceptor.collision(&Bandit);	//remove Bandit parameter here as it is redundant

	}

	// WHAT TO DO WITH SIMULATION TIME??
	
	float SimulationTime = NrOfUpdates / Params::PhysicsTimeStepsPerSecond;	// in seconds

	return (CollisionDetection * (1 - SimulationTime / 10) + !CollisionDetection * (1 / ClosestDistance * SimulationTime));
}