#pragma once
#include <vector>
#include "Utilities.h"
#include "Params.h"
#include "Population.h"

 

struct sNeuron {

	std::vector<float> weights;		//weights for each input
	
	sNeuron(int nr0fInputs);
};


struct sNeuronLayer {

	int nr0fNeurons;
	std::vector<sNeuron> one_neuronLayer;
	
	sNeuronLayer(int nr0fNeurons, int nr0fInputsPerNeuron);
};

class NeuralNet {
private:
	std::vector<sNeuronLayer> all_neuronLayers;

public:
	
	NeuralNet() { createNet();  }
	
	void createNet();
	void feedWeights(std::vector<float> inputWeights);
	std::vector<float> getWeights();
	std::vector<float> evaluate(std::vector<float>);
};