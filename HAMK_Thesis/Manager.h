#pragma once
#include <iostream>
#include "NeuralNet.h"
#include "Interceptor.h"
#include "Bandit.h"
#include "Target.h"

//#include "Object.h"

//#include "RocketController.h"

//#include "Population.h"
//#include "RocketNN.h"
//#include "Params.h"



//


class Manager {
public:
	Manager() {
		
		I1 = Interceptor(Params::posRocketNN, Params::angleRocketNN);
		POP1 = Population();
		NN1 = NeuralNet();

		B1 = Bandit(Params::posRocketOPP, Params::angleRocketOPP);

		TargetB1 = Target();

		I1.DefineTarget(&B1);
		B1.DefineTarget(&TargetB1);
	}
	
	
	virtual bool Simulate() = 0;
	

	void Run();
	void Save(std::ostream& out, const sGenome& genome);
	void Load(std::istream& in, sGenome& genome);
	void SaveAll();
	void LoadAll();
	void SaveBestGenome();
	sGenome LoadBestGenome();

	void ManageTopGenomes(int topN);
	std::vector<sGenome> LoadTopGenomes();

	Interceptor I1;
	Population POP1;
	NeuralNet NN1;

	Bandit B1;

	Target TargetB1;

	int iGeneration = 1;
	int iGenome;
	float SimuTimeInSec = 0.0f; // fps dependant

};