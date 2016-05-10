#pragma once
#include <iostream>

#include "RocketController.h"
#include "NeuralNet.h"
#include "Population.h"
#include "RocketNN.h"
#include "Params.h"



class Manager {
public:
	Manager() {
		
		TheNet = NeuralNet();
		
		CurrentPopulation = Population();
		
		Interceptor = RocketNN(Params::posRocketNN, Params::velRocketNN, Params::angleRocketNN);

		Bandit = RocketRND(Params::posRocketOPP, Params::velRocketOPP, Params::angleRocketOPP);

		Interceptor.DefineTarget(&Bandit);
	}
	
	
	virtual float Simulate() = 0;
	

	void Run();
	void Save(std::ostream& out, const sGenome& genome);
	void Load(std::istream& in, sGenome& genome);
	void SaveAll();
	void LoadAll();

	float CalculateDistance();
	
	bool OutOfBounds();	// might be redundant from RocketController
	
	RocketNN Interceptor;
	RocketRND Bandit;

	NeuralNet TheNet;
	Population CurrentPopulation;

	int iGeneration;	// index of Generation
	int iGenome;		// index of Genome

};