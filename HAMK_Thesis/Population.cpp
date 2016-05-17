#include <vector>
#include <iostream>

#include "Population.h"


// ************ Population ***************//
sGenome Population::BuildRandomGenome() {

	std::vector<float> RandomGenome;

	for (int i = 0; i < Params::WeightCount; ++i) {
		RandomGenome.push_back(randfloat(-1, 1));
	}

	return sGenome(RandomGenome);
}

void Population::BuildRandomPopulation() {

	for (int i = 0; i < Params::PopulationSize; ++i) {
		Genomes.push_back(BuildRandomGenome());
	}
}

void Population::SortPopulation() {

	std::sort(Genomes.begin(), Genomes.end(), [](const sGenome& lhs, const sGenome& rhs) {
		return lhs.fitness > rhs.fitness;
	}		// [] ... "lambda fgv", beagyazott fgv, impliciten bool-t ad vissza
	);
}

float Population::CalculateAverageFitness() {
	

	float sum = 0.0f;

	for (int i = 0; i < Params::PopulationSize; ++i) {
		sum += Genomes[i].fitness;
	}

	return sum / Params::PopulationSize;

}

float Population::getBestFitness() {

	return std::max_element(Genomes.begin(), Genomes.end(), [](const sGenome& lhs, const sGenome& rhs) {
		return lhs.fitness < rhs.fitness;
	}
	) ->fitness;
	
}

std::vector<sGenome> Population::pickBests(int topN, int copies) {

	std::vector<sGenome> returnvector;

	for (unsigned i = 0; i < topN; ++i) {
		for (unsigned j = 0; j < copies; ++j) {
			//Genomes[i].fitness = 0;
			returnvector.push_back(Genomes[i]);
		}
	}
	return returnvector;
}

void Population::Evolve() {

	SortPopulation();

	std::vector<sGenome> NewPopulation = pickBests(4, 1); 



	while (NewPopulation.size() != Genomes.size()) {
		std::vector<sGenome> Parents;
		Parents.push_back(Roulette());
		Parents.push_back(Roulette());

		while (Parents[0].value == Parents[1].value)
			Parents[1] = Roulette();	//Say no to Eric C.

		std::vector<sGenome> ParentsCrossedOver = Crossover2(Parents);
		std::vector<sGenome> SpecimensMutated = Mutate2(ParentsCrossedOver);

		//SpecimensMutated[0].fitness = 0;
		//SpecimensMutated[1].fitness = 0;


		NewPopulation.push_back(SpecimensMutated[0]);
		NewPopulation.push_back(SpecimensMutated[1]);
	}
	Genomes = NewPopulation;

	for (sGenome& genome : Genomes) {	// reset fitness scores to 0
		genome.fitness = 0;
	}

}

std::vector<sGenome> Population::Crossover2(std::vector<sGenome> Parents) {	//miert nem 2 kulon parameter?
	
	float CrossoverRate = 0.7f;		// Params
	
	if (randfloat() <= CrossoverRate) {
		int RandomCrossoverPoint = rand() % Params::WeightCount;

		for (int i = RandomCrossoverPoint; i < Params::WeightCount; ++i) {
			std::swap(Parents[0].value[i], Parents[1].value[i]);
		}

		std::vector<sGenome> NewParents;
		NewParents.push_back(Parents[0]);
		NewParents.push_back(Parents[1]);

		return NewParents;
	}
	else
		return Parents;
}

std::vector<sGenome> Population::Mutate2(std::vector<sGenome> Specimens) {	//miert nem 2 kulon parameter?
	float MutationRate = 0.005;

	bool ChangesDone = false;

	for (int i = 0; i < Specimens[0].value.size(); ++i) {
		if (randfloat() <= MutationRate) {
			Specimens[0].value[i] = 1 - Specimens[0].value[i];
			ChangesDone = true;
		}
	}
	for (int i = 0; i < Specimens[1].value.size(); ++i) {
		if (randfloat() <= MutationRate) {
			Specimens[1].value[i] = 1 - Specimens[1].value[i];
			ChangesDone = true;
		}
	}

	if (ChangesDone) {
		std::vector<sGenome> returnvector;
		returnvector.push_back(Specimens[0]);
		returnvector.push_back(Specimens[1]);

		return returnvector;
	}
		return Specimens;
}

sGenome Population::Roulette() {

	float Sum = 0.0f;
	float FitnessSoFar = 0.0f;

	for (int i = 0; i < Params::PopulationSize; ++i) {
		Sum += Genomes[i].fitness;
	}

	double Slice = (double)(randfloat() * Sum); 

	for (int i = 0; i < Params::PopulationSize; ++i) {	// redundant?
		FitnessSoFar += Genomes[i].fitness;

		if (FitnessSoFar >= Slice)
			return Genomes[i];
	}
	return Genomes.back();

}

