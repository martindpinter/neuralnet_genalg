#include "RocketNN.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include "RocketRND.h"

void RocketNN::controlls() {

	if (NNControls[0] > 0.4) {
		accelerate(NNControls[0]);
	}

	if (NNControls[1] < 0.5 - Params::NNC_Deadzone) {	//jatszogatni
		angular_accelerate(-0.5 - Params::NNC_Deadzone - NNControls[1]);
	}

	if (NNControls[1] > 0.5 + Params::NNC_Deadzone) {
		angular_accelerate(NNControls[1]);
	}
}

void RocketNN::reset() {
	position = Params::posRocketNN;
	velocity = Params::velRocketNN;
	angle = Params::angleRocketNN;
	throttle = 0.0f;
	angular_throttle = 0.0f;
	angular_velocity = 0.0f;
	rotationalSum = 0.0f;
}

void RocketNN::SetNNControls(NeuralNet *NN) {
	NNControls = NN->evaluate(getNNinputs());
}

void RocketNN::DefineTarget(RocketController  *EnemyRocket) {
	LockOnTarget = EnemyRocket;
}

void RocketNN::Set_vecPopulation(std::vector<float> returnvector) {

	vecPopulation = returnvector;
}

std::vector<float> RocketNN::getNNinputs() {

	std::vector<float> returnvector;


	float Egocent_x = LockOnTarget->position.x - position.x;

	float Egocent_y = LockOnTarget->position.y - position.y;

	float EgocentV_x = LockOnTarget->velocity.x - velocity.x;

	float EgocentV_y = LockOnTarget->velocity.y - velocity.y;


	// INPUT 0 :: Sebessegvektor hossza
	
	float VelocityVectorLength = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	
	float normVelocityVectorLength = normalize(VelocityVectorLength, 0, 20);		// 20 is only a guess based on measurements
	
	returnvector.push_back(normVelocityVectorLength);


	// INPUT 1 :: Facevector es sebessegvector iranyanak kulonbsege
	
	float VeloVec_xAxisDegree = atan2(velocity.y, velocity.x);
	
	float VelocityFaceOffset = angle - VeloVec_xAxisDegree;		// SWAPPED

	returnvector.push_back(normalize(VelocityFaceOffset, 0, 2 * Params::pi));	// check again


	// INPUT 2 :: Celraketa sebessegvektoranak x-tengellyel bezart szoge radianban
	
	float EnemyVelocity_xAxisDegree = atan2(EgocentV_y, EgocentV_x);
	
	float normEVxAD = normalize(EnemyVelocity_xAxisDegree, 0, 2 * Params::pi);		 

	if (normEVxAD < 0) {		// CSUNYAVAGYNAGYON :(((((((
		normEVxAD += 1;
	}

	returnvector.push_back(normEVxAD);
	

	// INPUT 3 :: Celraketa iranya az elfogohoz kepest (Left 0.0 ... [Centre-> 0.5 <-Centre] ... 1.0 Right)

	returnvector.push_back(LookAt(LockOnTarget));

	return returnvector;
}
