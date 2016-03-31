#pragma once
#include <vector>
#include "Utilities.h"
#include "cParams.h"
#include "cPopulation.h"	//korbeinclude veszely?
#include "cRocketRND.h"

 

struct sNeuron {

	int nr0fInputs;						//number of inputs
	std::vector<float> weights;		//weights for each input
	
	sNeuron(int nr0fInputs);
};


struct sNeuronLayer {

	int nr0fNeurons;
	std::vector<sNeuron> one_neuronLayer;
	
	sNeuronLayer(int nr0fNeurons, int nr0fInputsPerNeuron);
};

class cNeuralNet {
private:
	

	float biasvalue = 1.0f;	// cParams!!

	std::vector<sNeuronLayer> all_neuronLayers;

public:
	
	cNeuralNet();
	
	void createNet();

	std::vector<float> getWeights();
	void feedWeights(std::vector<float> inputWeights);

	std::vector<float> evaluate(std::vector<float>);

	float Sigmoid(float activation);
};