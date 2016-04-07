#pragma once
#include <vector>
#include "Utilities.h"
#include "cParams.h"
#include <iostream>

struct sGenome {	// egy raketat a-z -ig vezerlo ertekek sora
	
	std::vector<float> value;
	float fitness;

	sGenome() { for (int i = 0; i < cParams::WeightCount; ++i) { value.push_back(0.0f);	} }	//empty genomes shall be filled with values of 0.0f

	sGenome(std::vector<float> inputvector) : value(inputvector) {}

	//https://github.com/r0mai/car-game/blob/master/src/GeneticPopulation.hpp
	//https://github.com/r0mai/car-game/blob/master/src/GeneticPopulation.cpp
};


class cPopulation {	//Qtsmanal genetic population
private:

	
		//ez a fo tag, a tobbi kb csak segedvaltozo

	sGenome BuildRandomGenome();

	//void ReadPopulationFromFile(); KESOBB!!
	

	sGenome Roulette();
	void SortPopulation();
	std::vector<sGenome> Crossover2(std::vector<sGenome>);
	std::vector<sGenome> Mutate2(std::vector<sGenome>);

public:

	std::vector<sGenome> Population;

	cPopulation() { BuildRandomPopulation(); }

	void BuildRandomPopulation();

	void Evolve();	// ezt a fuggvenyt akkor hivjuk meg, ha a populacio osszes elemenek
					// fitness erteke be van allitva.
};