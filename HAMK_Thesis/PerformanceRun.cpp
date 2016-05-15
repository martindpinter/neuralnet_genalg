#include "PerformanceRun.h"

bool PerformanceRun::Simulate() {

	int NrOfUpdates = 0;

	NN1.feedWeights(POP1.Genomes[iGenome].value);
	NN2.feedWeights(POP2.Genomes[iGenome].value);

	while (true) {
		if (I1.Collided || B1.Collided) { break; }

		if (I1.isOOB() && B1.isOOB()) { break; }

		if (NrOfUpdates / Params::PhysicsTimeStepsPerSecond >= Params::MaxSimulationTime) { break; }

		I1.SetNNControls(&NN1);
		I1.update();

		B1.SetNNControls(&NN2);
		B1.update();

		NrOfUpdates++;
	}

	float SimulationTime = NrOfUpdates / Params::PhysicsTimeStepsPerSecond;	// in seconds
	POP1.Genomes[iGenome].fitness = I1.calcFitness(SimulationTime);
	POP2.Genomes[iGenome].fitness = B1.calcFitness(SimulationTime);

	return false;
}


//float PerformanceRun::Simulate() {
//	
//	sf::Clock SimulationClock;
//
//	bool CollisionDetection = false;
//
//	float ClosestDistance = sqrt(pow(Params::WindowHeight, 2) + pow(Params::WindowWidth, 2));
//
//	signed LookAtScore = 0;
//
//	int NrOfUpdates = 0;
//
//	while (!CollisionDetection && !isOOB()) {
//
//		I1.SetNNControls(&NN1);
//		// Bandit's controls should be given here instead of static movement
//
//
//		I1.update();
//		B1.update();
//		NrOfUpdates++;
//
//		float LookAtEnemy = I1.LookAt(&B1);
//
//		if (LookAtEnemy > 0.48 && LookAtEnemy < 0.52)
//			LookAtScore++;
//		else
//			LookAtScore--;
//
//
//		CollisionDetection = I1.collision(&B1);	//remove Bandit parameter here as it is redundant
//
//	}
//
//	// WHAT TO DO WITH SIMULATION TIME??
//	
//	float SimulationTime = NrOfUpdates / Params::PhysicsTimeStepsPerSecond;	// in seconds
//
//
//	if (CollisionDetection) {
//		return (Sigmoid(Params::MaxSimulationTime - SimulationTime, 5.0) + 1 + (LookAtScore * 0.001));
//	}
//	else {
//		return(Sigmoid(Params::MaxSimulationTime / (ClosestDistance * SimulationTime)) + (LookAtScore * 0.001));
//	}
//	
//	//return (CollisionDetection * (1 - SimulationTime / 10) + !CollisionDetection * (1 / ClosestDistance * SimulationTime));
//}