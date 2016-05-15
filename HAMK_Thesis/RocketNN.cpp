#include "RocketNN.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include "RocketRND.h"

void RocketNN::update() {
	RocketController::update();
	
	calcDistance();
	calcLookAtScore();
	CheckForSpin();
	CollisionDetection();
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

void RocketNN::DefineTarget(Object * EnemyRocket) {
	LockOnTarget = EnemyRocket;
}

void RocketNN::calcDistance() {

	ClosestDistanceToTarget = (sqrt(pow((LockOnTarget->position.x - position.x), 2) + pow((LockOnTarget->position.y - position.y), 2)));
}

void RocketNN::CollisionDetection() {

	float dx = position.x - LockOnTarget->position.x;
	float dy = position.y - LockOnTarget->position.y;
	float distance = sqrt(dx * dx + dy * dy);

	Collided = distance < (20 + 20);
}

//Celraketa iranya az elfogohoz kepest(Left 0.0 ...[Centre-> 0.5 <-Centre] ... 1.0 Right)
float RocketNN::normalizedLookAt() {
	
	float Egocent_x = LockOnTarget->position.x - position.x;
	float Egocent_y = LockOnTarget->position.y - position.y;

	float Angle_reltoX = atan2(Egocent_y, Egocent_x);
	float Difference = 2 * Params::pi - angle - Angle_reltoX;

	float normDifference = normalize(Difference, -1 * Params::pi, 1 * Params::pi);

	return normDifference;

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
		float returnvalue = Sigmoid(Params::MaxSimulationTime - SimulationTime, 5.0) + 1; //+ (LookAtScore * 0.001);

		if (SpinAlert)
			return returnvalue;
		else
			return  2 * returnvalue;
	}
	else {
		float returnvalue = Sigmoid(Params::MaxSimulationTime / (ClosestDistanceToTarget * SimulationTime)); // +(LookAtScore * 0.001);

		if (SpinAlert)
			return returnvalue / 2;
		else
			return returnvalue;
	}

}

//float RocketNN::calcFitness(float SimulationTime) {
//
//	if (Collided) {
//
//		float returnvalue = Sigmoid(Params::MaxSimulationTime - SimulationTime, 5.0) + 1 + (LookAtScore * 0.001);
//
//		if (SpinAlert)
//			return returnvalue;
//		else
//			return returnvalue + 0.5f;
//	}
//	else {
//		float returnvalue = Sigmoid(Params::MaxSimulationTime / (ClosestDistanceToTarget * SimulationTime)) + (LookAtScore * 0.001);
//
//		if (SpinAlert)
//			return returnvalue - 0.5;
//		else
//			return returnvalue;
//	}
//
//}