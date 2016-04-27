#include "cPopulation.h"
#include <vector>
#include <fstream>
#include <iostream>

// ************ cPopulation ***************//
sGenome cPopulation::BuildRandomGenome() {

	std::vector<float> RandomGenome;

	float maxWeight = 1 / sqrt(cParams::nr0fInputs);

	for (int i = 0; i < cParams::WeightCount; ++i) {
		RandomGenome.push_back(randfloat(-1, 1));
	}
	return sGenome(RandomGenome);
}

std::vector<sGenome> cPopulation::Crossover2(std::vector<sGenome> Parents) {	//miert nem 2 kulon parameter?
	
	float CrossoverRate = 0.7f;		// cParams
	
	if (randfloat() <= CrossoverRate) {
		int RandomCrossoverPoint = rand() % cParams::WeightCount;

		for (int i = RandomCrossoverPoint; i < cParams::WeightCount; ++i) {
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

std::vector<sGenome> cPopulation::Mutate2(std::vector<sGenome> Specimens) {	//miert nem 2 kulon parameter?
	float MutationRate = 0.001;

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

void cPopulation::Evolve() {

	
	SortPopulation();

	std::vector<sGenome> NewPopulation;

	while (NewPopulation.size() != Population.size()) {
		std::vector<sGenome> Parents;
		Parents.push_back(Roulette());
		Parents.push_back(Roulette());

		//while (Parents[0].value == Parents[1].value)
			//Parents[0] = Roulette();	//Say no to Eric C.

		std::vector<sGenome> ParentsCrossedOver = Crossover2(Parents);
		std::vector<sGenome> SpecimensMutated = Mutate2(ParentsCrossedOver);
			
		NewPopulation.push_back(SpecimensMutated[0]);
		NewPopulation.push_back(SpecimensMutated[1]);
	}
	Population = NewPopulation;
		
	/*		"serialization"
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		std::ofstream OutputFile;
		OutputFile.open("../LatestPopulation.txt");
		for (int i = 0; i < cParams::PopulationSize; ++i) {
			for (int j = 0; j < cParams::WeightCount; ++j) {
				OutputFile << Population[i].value[j] << " ";
			}
			OutputFile << std::endl;
		}
		OutputFile.close();
	}*/
}

void cPopulation::SortPopulation() {

	std::sort(Population.begin(), Population.end(), [](const sGenome& lhs, const sGenome& rhs) {
		return lhs.fitness > rhs.fitness;
		}		// [] ... "lambda fgv", beagyazott fgv, impliciten bool-t ad vissza
	);
}

sGenome cPopulation::Roulette() {

	float Sum = 0.0f;
	float FitnessSoFar = 0.0f;

	for (int i = 0; i < cParams::PopulationSize; ++i) {
		Sum += Population[i].fitness;
	}

	double Slice = (double)(randfloat() * Sum); 

	for (int i = 0; i < cParams::PopulationSize; ++i) {	// redundant?
		FitnessSoFar += Population[i].fitness;

		if (FitnessSoFar >= Slice)
			return Population[i];
	}
	return Population.back();

}

void cPopulation::BuildRandomPopulation() {

	for (int i = 0; i < cParams::PopulationSize; ++i) {
		Population.push_back(BuildRandomGenome());
	}
}

//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^