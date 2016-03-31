#pragma once
#include <SFML/Graphics.hpp>
#include "cRocketController.h"
#include "cParams.h"
#include "cNeuralNet.h"

class cRocketNN : public cRocketController {
public:
	cRocketNN(sf::Vector2f position, sf::Vector2f velocity, float angle) : cRocketController(position, velocity, angle, "../images/resized_by5/BlueRocket.png", "../images/resized_by5/BlueRocket_throttle.png") {}

	virtual void controlls(float frametime) override;	//virtual!!!

	
	cRocketController * LockOnTarget;	
	
	std::vector<float> vecPopulation;
	std::vector<float> NNControls;
	

	std::vector<float> getNNinputs();
	void SetNNControls(cNeuralNet *NN);
	
	void DefineTarget(cRocketController * EnemyRocket);

	void Set_vecPopulation(std::vector<float>);


	//std::vector<float> GetNNOutputs(const cNeuralNet& NN);

};