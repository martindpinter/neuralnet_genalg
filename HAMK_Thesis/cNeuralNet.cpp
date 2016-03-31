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
	int weightIndex = 0;
																								//kiindexel :(
	for (int i = 0; i < all_neuronLayers.size(); ++i) {

		for (int j = 0; j < all_neuronLayers[i].nr0fNeurons; ++j) {

			for (int k = 0; k < all_neuronLayers[i].one_neuronLayer[j].weights.size(); ++k) {	// nr0fInputs nincs inicializalva
				all_neuronLayers[i].one_neuronLayer[j].weights[k] = inputWeights[weightIndex++];
			}
		}
	}
}

/*
void cNeuralNet::feedWeights(std::vector<float> inputWeights) {

	int weightIndex = 0;
	
	for (int i = 0; i < all_neuronLayers.size(); ++i) {
		
		for (int j = 0; j < all_neuronLayers[i].one_neuronLayer.size(); ++j) {
			
			for (int k = 0; k < all_neuronLayers[i].one_neuronLayer[j].weights.size(); ++k) {
				// this only works if there are already a weights(rnd) pre-set,
				// so the number of weights would remain the same (size();)
				all_neuronLayers[i].one_neuronLayer[j].weights[k] = inputWeights[weightIndex++];
			}
		}
	}
}
*/
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
	std::vector<float> oneLayerOutputs;
	
	for (int i = 0; i < cParams::nr0fHiddenLayers + 1; ++i) {	// each layer i

		if (i > 0)	
			inputvector = oneLayerOutputs;

		for (int j = 0; j < all_neuronLayers[i].nr0fNeurons; ++j) {		// each neuron j

			float total = 0.0f;
			
			
			for (int k = 0; k < all_neuronLayers[i].one_neuronLayer[j].nr0fInputs; ++k) {	// each weight k
				
				if (k != all_neuronLayers[i].one_neuronLayer[j].nr0fInputs - 1)	// if this is NOT the last weight
					total += all_neuronLayers[i].one_neuronLayer[j].weights[k] * inputvector[k];
				else
					total += all_neuronLayers[i].one_neuronLayer[j].weights[k] * biasvalue;
			}

				oneLayerOutputs.push_back(Sigmoid(total));
		}
	}
	return oneLayerOutputs;
}

float cNeuralNet::Sigmoid(float activation) {
	
	float response = 1.0f;
	return (1 / (1 + exp(-activation / response)));
}