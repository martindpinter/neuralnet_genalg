#include <fstream>
#include "Manager.h"
#include "Params.h"

void Manager::Run() {
	for (iGeneration = 1; iGeneration < Params::MaxGenerations; ++iGeneration) {

		for (iGenome = 0; iGenome < Params::PopulationSize; ++iGenome) {

			Interceptor.reset();
			Bandit.reset();

			TheNet.feedWeights(CurrentPopulation.ThePopulation[iGenome].value);

			CurrentPopulation.ThePopulation[iGenome].fitness = Simulate();

		}
		CurrentPopulation.Evolve();
	}
}

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

	std::fstream loadStream;
	std::string line;
	loadStream.open("SaveFile.txt", std::ios::in);
	
	int iLine = 0;

	std::vector<sGenome> returnGenomes;

	while (getline(loadStream, line)) {
		for (int CharStep = 0; CharStep < line.size(); ++CharStep) {
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

float Manager::CalculateDistance() {
	
	return (sqrt(pow((Bandit.position.x - Interceptor.position.x), 2) + pow((Bandit.position.y - Interceptor.position.y), 2)));
}

bool Manager::OutOfBounds() {
	
	if (Interceptor.OutOfBounds()) {
		
		std::cout << "Interceptor has gone out of bounds." << std::endl;
		
		return true;
	}
	
	// If EnemyRocket left the zone
	if (Bandit.OutOfBounds()) {
		
		std::cout << "EnemyRocket has gone out of bounds." << std::endl;
		
		return true;
	}

	return false;
}
