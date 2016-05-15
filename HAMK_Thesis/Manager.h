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

		//CurrentPopulation = Population();
		
		B1 = Bandit(Params::posRocketOPP, Params::angleRocketOPP);
		POP2 = Population();
		NN2 = NeuralNet();

		City = Target();

		I1.DefineTarget(&B1);
		B1.DefineTarget(&City); // BE KELL VEZETNI OBJECT CLASS-t, NINCS MESE :(
	}
	
	
	virtual bool Simulate() = 0;
	

	void Run();
	void Save(std::ostream& out, const sGenome& genome);
	void Load(std::istream& in, sGenome& genome);
	void SaveAll();
	void LoadAll();
	
	//bool isOOB();	// might be redundant from RocketController
	
	//NeuralNet TheNet;

	Interceptor I1;
	Population POP1;
	NeuralNet NN1;

	Bandit B1;
	Population POP2;
	NeuralNet NN2;

	Target City;
	
	Population CurrentPopulation;

	int iGeneration;	// index of Generation
	int iGenome;		// index of Genome

	float SimuTimeInSec = 0.0f; // fps dependant

};