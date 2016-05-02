#include "cNeuralNet.h"


sNeuron::sNeuron(int nr0fInputs) {
	for (int i = 0; i < nr0fInputs + 1; ++i) {	// +1 since the bias
		weights.push_back(randClamped());	// GenAlg
											// std::vector<float> tarolja az ossssszesss weightet, GenAlg cserelgeti
	}
}

sNeuronLayer::sNeuronLayer(int nr0fNeurons, int nr0fInputsPerNeuron) : nr0fNeurons(nr0fNeurons) {
	
	for (int i = 0; i < nr0fNeurons; ++i) {

		one_neuronLayer.push_back(sNeuron(nr0fInputsPerNeuron));
	}
}

cNeuralNet::cNeuralNet() {

	createNet();
}

std::vector<float> cNeuralNet::getWeights() {

	std::vector<float> outputvector;
	
	for (int i = 0; i < all_neuronLayers.size(); ++i) {		// each layer i
		
		for (int j = 0; j < all_neuronLayers[i].one_neuronLayer.size(); ++j) {	// each layer j
			
			for (int k = 0; k < all_neuronLayers[i].one_neuronLayer[j].weights.size(); ++k) {
			
				outputvector.push_back(all_neuronLayers[i].one_neuronLayer[j].weights[k]);
			}
		}
	}
	return outputvector;
}

void cNeuralNet::feedWeights(std::vector<float> inputWeights) {
	if (inputWeights.size() != cParams::WeightCount) {
		std::cout << "The number of input weights does not match the weight count." << std::endl;
	}
	else {
		int weightIndex = 0;
		for (int i = 0; i < all_neuronLayers.size(); ++i) {								// for each layer
			for (int j = 0; j < all_neuronLayers[i].one_neuronLayer.size(); ++j) {		// for each neuron
				for (int k = 0; k < all_neuronLayers[i].one_neuronLayer[j].weights.size(); ++k) {	// for each weight
					all_neuronLayers[i].one_neuronLayer[j].weights[k] = inputWeights[weightIndex++];

				}

			}
		}
	}
}

void cNeuralNet::createNet() {
	//Creates the structure of layers
	if (cParams::nr0fHiddenLayers > 0) {
		for (int i = 0; i < cParams::nr0fHiddenLayers; ++i) {

			if (i == 0)
				all_neuronLayers.push_back(sNeuronLayer(cParams::NeuronsPerHiddenLayer, cParams::nr0fInputs));
			else
				all_neuronLayers.push_back(sNeuronLayer(cParams::NeuronsPerHiddenLayer, cParams::NeuronsPerHiddenLayer));
		}
		all_neuronLayers.push_back(sNeuronLayer(cParams::nr0fOutputs, cParams::NeuronsPerHiddenLayer));
	}
	else {
		all_neuronLayers.push_back(sNeuronLayer(cParams::nr0fOutputs, cParams::nr0fInputs));
	}
}

std::vector<float> cNeuralNet::evaluate(std::vector<float> inputvector) {
	// Runs through a vector of inputs (what the rocket "sees") through each layer of the neural net,
	// returning the last layer of sigmoids.
	
	std::vector<float> OneLayerInputs = inputvector;
	std::vector<float> OneLayerOutputs;
	std::vector<float> OutputVector;

	// Evaluating through the Input Layer and Hidden Layers

	for (int i = 0; i < cParams::nr0fHiddenLayers; ++i) { // nem adunk hozza +1et, mert az output layert kulon kezeljuk
		if (i > 0) {
			OneLayerInputs = OneLayerOutputs;
		}

		for (int j = 0; j < all_neuronLayers[i].one_neuronLayer.size(); ++j) {		// each neuron

			float total = 0.0f;

			for (int k = 0; k < all_neuronLayers[i].one_neuronLayer[j].weights.size(); ++k) {	// each weight
				if (k != all_neuronLayers[i].one_neuronLayer[j].weights.size() - 1) {	// if ordinary weight
					total += all_neuronLayers[i].one_neuronLayer[j].weights[k] * OneLayerInputs[k];
				}
				else {
					total += all_neuronLayers[i].one_neuronLayer[j].weights[k] * cParams::BiasValue;
				}

			}
			OneLayerOutputs.push_back(Sigmoid(total));
		}
	}

	OneLayerInputs = OneLayerOutputs;

	// Evaluating through the Output layer

	for (int i = 0; i < cParams::nr0fOutputs; ++i) {
		
		float total = 0.0f;

		for (int j = 0; j < all_neuronLayers.back().one_neuronLayer[i].weights.size(); ++j) {
			if (j != all_neuronLayers.back().one_neuronLayer[i].weights.size() - 1) {	// if ordinary weight
				total += all_neuronLayers.back().one_neuronLayer[i].weights[j] * OneLayerOutputs[j];
			}
			else {
				total += all_neuronLayers.back().one_neuronLayer[i].weights[j] * cParams::BiasValue;
			}
		}

		OutputVector.push_back(Sigmoid(total));
	}

	return OutputVector;
}

float cNeuralNet::Sigmoid(float activation) {
	
	float response = 1.0f;
	return (1 / (1 + exp(-activation / response)));
}