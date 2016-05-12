#include "PerformanceRun.h"

float PerformanceRun::Simulate() {
	
	sf::Clock SimulationClock;

	bool CollisionDetection = false;

	float ClosestDistance = sqrt(pow(Params::WindowHeight, 2) + pow(Params::WindowWidth, 2));

	signed LookAtScore = 0;

	int NrOfUpdates = 0;

	while (!CollisionDetection && !OutOfBounds()) {

		Interceptor.SetNNControls(&TheNet);
		// Bandit's controls should be given here instead of static movement


		Interceptor.update();
		Bandit.update();
		NrOfUpdates++;

		float LookAtEnemy = Interceptor.LookAt(&Bandit);

		if (LookAtEnemy > 0.48 && LookAtEnemy < 0.52)
			LookAtScore++;
		else
			LookAtScore--;


		CollisionDetection = Interceptor.collision(&Bandit);	//remove Bandit parameter here as it is redundant

	}

	// WHAT TO DO WITH SIMULATION TIME??
	
	float SimulationTime = NrOfUpdates / Params::PhysicsTimeStepsPerSecond;	// in seconds


	if (CollisionDetection) {
		return (Sigmoid(Params::MaxSimulationTime - SimulationTime, 5.0) + 1 + (LookAtScore * 0.001));
	}
	else {
		return(Sigmoid(Params::MaxSimulationTime / (ClosestDistance * SimulationTime)) + (LookAtScore * 0.001));
	}
	
	//return (CollisionDetection * (1 - SimulationTime / 10) + !CollisionDetection * (1 / ClosestDistance * SimulationTime));
}