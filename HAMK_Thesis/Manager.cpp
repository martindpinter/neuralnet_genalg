#include <fstream>
#include "Manager.h"
#include "Params.h"
#include <fstream>
#include <iomanip>

void Manager::Run() {
	bool isEnded = false;

	for (iGeneration = 1; iGeneration < Params::MaxGenerations && !isEnded; ++iGeneration) {

		for (iGenome = 0; iGenome < Params::PopulationSize && !isEnded; ++iGenome) {

			// if window is closed bool breakeljen ki --> break;

			I1.reset();
			B1.reset();

			isEnded = Simulate();
			
			std::cout << std::fixed << std::setprecision(6) << iGeneration << " / " << Params:: MaxGenerations << " :: " << iGenome << " / " << Params::PopulationSize << "   @ " << POP1.Genomes[iGenome].fitness << "                ";
			std::cout << " @ " << POP2.Genomes[iGenome].fitness << std::endl;

		}
		POP1.Evolve();
		POP2.Evolve();
		
		SaveAll();
		std::cout << std::endl << "Saved successfully" << std::endl;
	}
}

void Manager::SaveAll() {
	
	std::ofstream out("SaveFile.txt");

	out << iGeneration << std::endl;

	out << iGenome << std::endl;

	out << POP1.Genomes.size() << std::endl;
	
	for (const sGenome& genome : POP1.Genomes) {
		Save(out, genome);
	}

	out << POP2.Genomes.size() << std::endl;

	for (const sGenome& genome : POP2.Genomes) {
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

	int genomeCounter = 0;
	for (sGenome& genome : newPopulation) {
		if (genomeCounter < PopulationSize) {
			Load(in, genome);
			genomeCounter++;
		}
	}

	POP1.Genomes = newPopulation;

	newPopulation.clear();

	PopulationSize = 0;
	in >> PopulationSize;
	newPopulation.resize(PopulationSize);

	for (sGenome& genome : newPopulation) {
		Load(in, genome);
	}

	POP2.Genomes = newPopulation;
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