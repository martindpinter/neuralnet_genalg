#pragma once
#include <vector>
#include "Utilities.h"
#include "Params.h"
#include <iostream>

struct sGenome {	// egy raketat a-z -ig vezerlo ertekek sora
	
	std::vector<float> value;
	float fitness;

	sGenome() { for (int i = 0; i < Params::WeightCount; ++i) { value.push_back(0.0f);	} }	//empty genomes shall be filled with values of 0.0f

	sGenome(std::vector<float> inputvector) : value(inputvector) {}

	//https://github.com/r0mai/car-game/blob/master/src/GenetiPopulation.hpp
	//https://github.com/r0mai/car-game/blob/master/src/GenetiPopulation.cpp
};


class Population {
private:
	sGenome BuildRandomGenome();

	//void ReadPopulationFromFile(); KESOBB!!

	sGenome Roulette();
	void SortPopulation();
	std::vector<sGenome> Crossover2(std::vector<sGenome>);
	std::vector<sGenome> Mutate2(std::vector<sGenome>);
	float CalculateAverageFitness();

public:

	Population() { BuildRandomPopulation(); }
	Population(std::vector<sGenome> inputVector) { Genomes = inputVector;	}

	std::vector<sGenome> Genomes;
	float AverageFitness;

	void BuildRandomPopulation();

	void Evolve();

};