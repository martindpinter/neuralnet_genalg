#include "RocketNN.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>

void RocketNN::update() {
	RocketController::update();
	
	calcDistance();
	calcLookAtScore();
	CheckForSpin();
	TargetHit();
}

void RocketNN::controls() {

	if (NNControls[0] > 0.4)
		accelerate(0.01f);
	else
		accelerate(-0.006f);

	if (NNControls[1] < 0.5 - Params::NNC_Deadzone)
		angular_accelerate(-0.01f);
	else if (NNControls[1] > 0.5 + Params::NNC_Deadzone)
		angular_accelerate(0.01f);
	else
		angular_accelerate((-1 * angular_throttle) / 30);
}

void RocketNN::SetNNControls(NeuralNet *NN) {
	NNControls = NN->evaluate(getNNinputs());
}



void RocketNN::calcDistance() {

	ClosestDistanceToTarget = (sqrt(pow((LockOnTarget->position.x - position.x), 2) + pow((LockOnTarget->position.y - position.y), 2)));
}

//Celraketa iranya az elfogohoz kepest(Left 0.0 ...[Centre-> 0.5 <-Centre] ... 1.0 Right)
float RocketNN::normalizedLookAt() {
	
	float Egocent_x = LockOnTarget->position.x - position.x;
	float Egocent_y = LockOnTarget->position.y - position.y;

	float Angle_reltoX = atan2(Egocent_y, Egocent_x);
	float Difference = 2 * Params::pi - angle - Angle_reltoX;

	float wrappedDifference = wrapRange(Difference, -Params::pi, Params::pi);

	return normalize(wrappedDifference, -Params::pi, Params::pi);

}

float RocketNN::calcLookAtScore() {

	float LookAtEnemy = normalizedLookAt();

	if (LookAtEnemy > 0.48 && LookAtEnemy < 0.52)
		LookAtScore++;
	else
		LookAtScore--;

	return 0.0f;
}

float RocketNN::calcFitness(float SimulationTime) {
	

	if (Collided) {
		//return Sigmoid(Params::MaxSimulationTime - SimulationTime, 0.3) + 1;
		return normalize(Params::MaxSimulationTime - SimulationTime, 0, Params::MaxSimulationTime) + 1;

	}
	else {
		//return Sigmoid(1400 - ClosestDistanceToTarget, 0.01);
		return normalize(1400 - ClosestDistanceToTarget, 0, 1400);
	}

}