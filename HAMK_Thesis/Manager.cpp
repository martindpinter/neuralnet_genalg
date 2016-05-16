#include <fstream>
#include "Manager.h"
#include "Params.h"
#include <fstream>
#include <iomanip>

void Manager::Run() {
	bool isEnded = false;

	//for (iGeneration = 1; iGeneration < Params::MaxGenerations && !isEnded; ++iGeneration) {
	for (iGeneration = iGeneration; !isEnded; ++iGeneration) {
		TargetB1.reset();
		

		for (iGenome = 0; iGenome < Params::PopulationSize && !isEnded; ++iGenome) {

			// if window is closed bool breakeljen ki --> break;

			I1.reset();
			B1.reset(iGeneration);				 // 8			

			POP1.Genomes[iGenome].initposTargetB1 = TargetB1.position;
			POP1.Genomes[iGenome].initposI1 = I1.position;
			POP1.Genomes[iGenome].initposB1 = B1.position;

			isEnded = Simulate();

			ManageTopGenomes(10);
		}
		std::cout << "Generation " << iGeneration << " ";
		std::cout << "Avg fitness: " << POP1.CalculateAverageFitness();
		std::cout << " Best fitness: " << POP1.getBestFitness() << std::endl;
		
		SaveBestGenome();
		
		POP1.Evolve();
		
		SaveAll();
		
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

}

void Manager::ManageTopGenomes(int topN) {
	if (POP1.Genomes[iGenome].fitness > 1) {
		std::vector<sGenome> TopGenomes;
		std::ifstream in("TopGenomes.txt");

		int size = 0;
		in >> size;

		if (size > 0) {
			TopGenomes.resize(size);

			for (sGenome& genome : TopGenomes) {
				Load(in, genome);
			}
		}
		in.close();

	
		TopGenomes.push_back(POP1.Genomes[iGenome]);

		std::sort(TopGenomes.begin(), TopGenomes.end(), [](const sGenome& lhs, const sGenome& rhs) { return lhs.fitness > rhs.fitness;	});

		while (TopGenomes.size() > topN)
			TopGenomes.pop_back();

		std::ofstream out("TopGenomes.txt");
		
		size = TopGenomes.size();

		out << size++ << std::endl;	 //  size??? size++?   APPEND!

		for (sGenome& genome : TopGenomes) {
			Save(out, genome);
		}
	}
	
}

std::vector<sGenome> Manager::LoadTopGenomes() {
	std::vector<sGenome> returnvector;
	std::ifstream in("TopGenomes.txt");

	int size = 0;
	in >> size;

	if (size > 0) {
		returnvector.resize(size);

		for (sGenome& genome : returnvector) {
			Load(in, genome);
		}
	}
	return returnvector;

}

void Manager::SaveBestGenome() {
	
	sGenome & BestGenome = *std::max_element(POP1.Genomes.begin(), POP1.Genomes.end(), [](const sGenome& lhs, const sGenome& rhs) { return lhs.fitness < rhs.fitness; });

	if (BestGenome.fitness > LoadBestGenome().fitness) {

		std::ofstream out("BestGenome.txt");

		out << BestGenome.fitness << std::endl;

		out << BestGenome.value.size() << std::endl;

		for (float value : BestGenome.value) {
			out << value << ' ';
		}

		out << std::endl;
		out << BestGenome.initposI1.x << ' ' << BestGenome.initposI1.y << ' ';
		out << BestGenome.initposB1.x << ' ' << BestGenome.initposB1.y << ' ';
		out << BestGenome.initposTargetB1.x << ' ' << BestGenome.initposTargetB1.y;

	}
}

sGenome Manager::LoadBestGenome() {
	std::ifstream in("BestGenome.txt");
	sGenome BestGenome;
	Load(in, BestGenome);

	/*std::cout << BestGenome.fitness << std::endl;
	std::cout << BestGenome.value.size() << std::endl;
	for (float value : BestGenome.value) {
		std::cout << value << " ";
	}*/
	
	in >> BestGenome.initposI1.x >> BestGenome.initposI1.y;
	in >> BestGenome.initposB1.x >> BestGenome.initposB1.y;
	in >> BestGenome.initposTargetB1.x >> BestGenome.initposTargetB1.y;

	return BestGenome;
}


void Manager::Save(std::ostream& out, const sGenome& genome) {

	out << genome.fitness << std::endl;

	out << genome.value.size() << std::endl;

	for (float value : genome.value) {
		out << value << ' ';
	}

	out << std::endl;
	out << genome.initposI1.x << ' ' << genome.initposI1.y << ' ';
	out << genome.initposB1.x << ' ' << genome.initposB1.y << ' ';
	out << genome.initposTargetB1.x << ' ' << genome.initposTargetB1.y << std::endl;
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
}

void Manager::Load(std::istream& in, sGenome& genome) {

	in >> genome.fitness;

	int size;
	in >> size;

	genome.value.resize(size);

	for (float& value : genome.value) {
		in >> value;
	}

	in >> genome.initposI1.x >> genome.initposI1.y;
	in >> genome.initposB1.x >> genome.initposB1.y;
	in >> genome.initposTargetB1.x >> genome.initposTargetB1.y;

}