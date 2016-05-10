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
/*
void Manager::Save() {
	std::fstream saveStream;
	saveStream.open("SaveFile.txt", std::ios::out);
	saveStream << "Generation: " << iGeneration;

	for (int i = 0; i < CurrentPopulation.ThePopulation.size(); ++i) {
		saveStream << std::endl << std::endl << "Fitness: " << CurrentPopulation.ThePopulation[i].fitness << std::endl;

		for (int j = 0; j < CurrentPopulation.ThePopulation[i].value.size(); ++j) {

			if (j > 0) {
				saveStream << " ";
			}

			saveStream << CurrentPopulation.ThePopulation[i].value[j];
		}
	}
	saveStream.close();
}

void Manager::Load() {

	std::ifstream loadStream;
	std::string line;
	loadStream.open("SaveFile.txt", std::ios::in);
	
	int iLine = 0;

	std::vector<sGenome> returnGenomes;

	while (getline(loadStream, line)) {
		for (int CharStep = 0; CharStep < line.size(); ++CharStep) {
			
			std::cout << line.size() << std::endl;

			if (line.size() > 0) {	// if not empty line  // WILL IT WORK LIKE THIS?
				
				std::vector<std::string> exploLine = explode(line, ' ');

				if (iLine == 0) {
					iGeneration = std::stoi(exploLine[1]);	// Set Generation
				}

				if (line[0] == 'F') {	// Create dummy genome and set its fitness
					returnGenomes.push_back(sGenome());
					returnGenomes.back().fitness = std::stoi(exploLine[1]);
				}


				if (exploLine.size() > 2) {
					for (int i = 0; i < returnGenomes.back().value.size(); ++i) {
						returnGenomes.back().value[i] = std::stof(exploLine[i]);
					}
				}

			}
		}
		++iLine;
	}

	loadStream.close();

}
*/  // old Save() and Load()

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
		
		//std::cout << "Interceptor has gone out of bounds." << std::endl;
		
		return true;
	}
	
	// If EnemyRocket left the zone
	if (Bandit.OutOfBounds()) {
		
		//std::cout << "EnemyRocket has gone out of bounds." << std::endl;
		
		return true;
	}

	return false;
}
