#include "cRocketNN.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include "cRocketRND.h"

void cRocketNN::controlls(float frametime) {

	if (NNControls[0] > 0.4) {
		accelerate(NNControls[0] * frametime);
	}
	if (NNControls[1] < 0.3) {	//jatszogatni
		angular_accelerate((0.5 + NNControls[1]) * frametime);
	}
	if (NNControls[1] > 0.7) {
		angular_accelerate(NNControls[1] * frametime);
	}
}

void cRocketNN::SetNNControls(cNeuralNet *NN) {
	NNControls = NN->evaluate(getNNinputs());
}

void cRocketNN::DefineTarget(cRocketController  *EnemyRocket) {
	LockOnTarget = EnemyRocket;
}

void cRocketNN::Set_vecPopulation(std::vector<float> returnvector) {

	vecPopulation = returnvector;
}



std::vector<float> cRocketNN::getNNinputs() {

	std::vector<float> returnvector;


	// INPUT 1 :: Sebessegvektor hossza
	float VelocityVectorLength = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(VelocityVectorLength);


	// INPUT 2 :: Facevector es sebessegvector iranyanak kulonbsege
	float VeloVec_xAxisDegree = rad2deg(atan2(velocity.y, velocity.x));
	float FaceVec_xAxisDegree = rad2deg(angle);
	
	float VelocityFaceOffset = VeloVec_xAxisDegree - FaceVec_xAxisDegree;
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(VelocityFaceOffset);


	// INPUT 3 :: Celraketa sebessegvektora.x	// hozzank kepes legyen relativ
	float EnemyVelocity_xAxisDegree = rad2deg(atan2(LockOnTarget->velocity.y, LockOnTarget->velocity.x));
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(EnemyVelocity_xAxisDegree - FaceVec_xAxisDegree);

	/*
	// INPUT 4 :: Celraketa sebessegvektora.y
	float EnemyVelovec_y = LockOnTarget->velocity.y;
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(EnemyVelovec_y);
	*/

	// INPUT 5 :: Celraketa iranya az elfogohoz kepest (Left -1.0 ... +1.0 Right)
	float Egocent_x = LockOnTarget->position.x - position.x;
	float Egocent_y = LockOnTarget->position.y - position.y;
	float RelativeAngle = atan2(Egocent_y, Egocent_x);

	float direction = RelativeAngle / 2 * 3.141592;
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(direction);


	return returnvector;
}
