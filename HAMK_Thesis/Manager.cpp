#include <fstream>
#include "Manager.h"
#include "Params.h"
#include <fstream>

void Manager::Run() {
	for (iGeneration = 1; iGeneration < Params::MaxGenerations; ++iGeneration) {

		for (iGenome = 0; iGenome < Params::PopulationSize; ++iGenome) {

			Interceptor.reset();
			Bandit.reset();

			TheNet.feedWeights(CurrentPopulation.ThePopulation[iGenome].value);

			CurrentPopulation.ThePopulation[iGenome].fitness = Simulate();
			
			std::cout << iGeneration << " / " << Params:: MaxGenerations << " :: " << iGenome << " / " << Params::PopulationSize << "   @ " << CurrentPopulation.ThePopulation[iGenome].fitness << std::endl;

		}
		CurrentPopulation.Evolve();
		
		SaveAll();
		std::cout << std::endl << "Saved successfully" << std::endl;
	}
}

void Manager::SaveAll() {
	
	std::ofstream out("SaveFile.txt");

	out << iGeneration << std::endl;

	out << iGenome << std::endl;

	out << CurrentPopulation.ThePopulation.size() << std::endl;
	
	for (const sGenome& genome : CurrentPopulation.ThePopulation) {
		Save(out, genome);
	}
}

void Manager::Save(std::ostream& out, const sGenome& genome) {

	out << genome.fitness << std::endl;

	out << genome.value.size() << std::endl;

	for (float value : genome.value) {
		out << value << ' ';
	}

	out << std::endl;
}

void Manager::LoadAll() {
	std::vector<sGenome> newPopulation;
	std::ifstream in("SaveFile.txt");
	in >> iGeneration;

	in >> iGenome;
	if (iGenome >= Params::PopulationSize)
		iGenome = 0;
	
	int PopulationSize;
	in >> PopulationSize;
	newPopulation.resize(PopulationSize);

	for (sGenome& genome : newPopulation) {
		Load(in, genome);
	}

	CurrentPopulation.ThePopulation = newPopulation;
}

void Manager::Load(std::istream& in, sGenome& genome) {

	in >> genome.fitness;

	int size;
	in >> size;

	genome.value.resize(size);

	for (float& value : genome.value) {
		in >> value;
	}

}

float Manager::CalculateDistance() {
	
	return (sqrt(pow((Bandit.position.x - Interceptor.position.x), 2) + pow((Bandit.position.y - Interceptor.position.y), 2)));
}

bool Manager::OutOfBounds() {
	
	if (Interceptor.OutOfBounds()) {		
		return true;
	}

	if (Bandit.OutOfBounds()) {
		return true;
	}
	return false;
}
