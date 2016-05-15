#pragma once
#include <SFML/Graphics.hpp>
#include "RocketController.h"
#include "Params.h"
#include "NeuralNet.h"

class RocketNN : public RocketController {
public:
	RocketNN() {}

	RocketNN(sf::Vector2f position, float angle) : RocketController(position, angle, "../images/resized_by5/BlueRocket.png", "../images/resized_by5/BlueRocket_throttle.png") {}  // do I need to pass position from layer to layer?

	

	virtual void CollisionDetection() override;
	virtual void controls() override;
	virtual void update() override;

	virtual std::vector<float> getNNinputs() = 0;

	void DefineTarget(Object * EnemyRocket);

	void calcDistance();
	float ClosestDistanceToTarget = sqrt(pow(Params::WindowHeight, 2) + pow(Params::WindowWidth, 2));
	
	float calcLookAtScore();
	float LookAtScore = 0;
	float normalizedLookAt();

	


	float calcFitness(float SimulationTime);

	Object * LockOnTarget;
	
	std::vector<float> vecPopulation;
	
	std::vector<float> NNControls;

	void SetNNControls(NeuralNet *NN);

};