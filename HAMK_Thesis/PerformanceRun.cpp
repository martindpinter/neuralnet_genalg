#include "PerformanceRun.h"

bool PerformanceRun::Simulate(float angle) {

	I1.angle = angle;

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
	
	if (POP1.Genomes[iGenome].fitness == 0)
		POP1.Genomes[iGenome].fitness = I1.calcFitness(SimuTimeInSec);
	else
		POP1.Genomes[iGenome].fitness += I1.calcFitness(SimuTimeInSec);

	return false;
}