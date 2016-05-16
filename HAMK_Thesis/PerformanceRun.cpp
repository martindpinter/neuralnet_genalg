#include "PerformanceRun.h"

bool PerformanceRun::Simulate() {

	int NrOfUpdates = 0;

	NN1.feedWeights(POP1.Genomes[iGenome].value);

	while (true) {
		if (I1.Collided || B1.Collided) { break; }

		if (I1.isOOB() && B1.isOOB()) { break; }

		if (NrOfUpdates / Params::PhysicsTimeStepsPerSecond >= Params::MaxSimulationTime) { break; }

		I1.SetNNControls(&NN1);
		I1.update();

		B1.update();

		TargetB1.update();

		NrOfUpdates++;
	}

	float SimulationTime = NrOfUpdates / Params::PhysicsTimeStepsPerSecond;	// in seconds
	POP1.Genomes[iGenome].fitness = I1.calcFitness(SimulationTime);

	return false;
}