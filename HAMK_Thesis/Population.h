#pragma once
#include <vector>
#include "Utilities.h"
#include "Params.h"
#include <iostream>

struct sGenome {
	
	std::vector<float> value;
	float fitness = 0;

	sGenome() : fitness(0) { for (int i = 0; i < Params::WeightCount; ++i) { value.push_back(0.0f);	} }

	sGenome(std::vector<float> inputvector) : value(inputvector) {}

	sf::Vector2f initposI1;
	sf::Vector2f initposB1;
	sf::Vector2f initposTargetB1;

};


class Population {
private:
	sGenome BuildRandomGenome();

	//void ReadPopulationFromFile(); KESOBB!!

	sGenome Roulette();
	void SortPopulation();
	std::vector<sGenome> Crossover2(std::vector<sGenome>);
	std::vector<sGenome> Mutate2(std::vector<sGenome>);
	std::vector<sGenome> pickBests(int topN, int copies);


public:

	Population() { BuildRandomPopulation(); }
	Population(std::vector<sGenome> inputVector) { Genomes = inputVector;	}

	std::vector<sGenome> Genomes;
	float AverageFitness;

	void BuildRandomPopulation();

	void Evolve();

	float CalculateAverageFitness();
	float getBestFitness();

};