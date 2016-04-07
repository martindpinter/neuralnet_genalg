#include "cRocketNN.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include "cRocketRND.h"

void cRocketNN::controlls(float frametime) {

	if (NNControls[0] > 0.4) {
		accelerate(NNControls[0] * frametime);
	}

	if (NNControls[1] < 0.2) {	//jatszogatni
		angular_accelerate((0.8 + NNControls[1]) * frametime);	// csak pozitivat ad, mindig jobbra fog menni
	}
	if (NNControls[1] > 0.8) {
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
	

	// INPUT 4 :: Celraketa iranya az elfogohoz kepest (Left -1.0 ... +1.0 Right)
	float Egocent_x = LockOnTarget->position.x - position.x;
	float Egocent_y = LockOnTarget->position.y - position.y;
	float RelativeAngle = atan2(Egocent_y, Egocent_x);

	float direction = RelativeAngle / 2 * 3.141592;
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(direction);
	
	//ne fuggjon az abszolut poziciotol, hanem a relativtol!!!


	/*
	returnvector.push_back(LockOnTarget->position.x);
	returnvector.push_back(LockOnTarget->position.y);
	returnvector.push_back(sqrt(  (LockOnTarget->position.x + LockOnTarget->velocity.x) * (LockOnTarget->position.x + LockOnTarget->velocity.x)
								+ (LockOnTarget->position.y + LockOnTarget->velocity.y) * (LockOnTarget->position.y + LockOnTarget->velocity.y)));
	// + LockOnTarget's position to left or right from facevector (maybe -1...1 or 0...1)?

	returnvector.push_back(position.x);
	returnvector.push_back(position.y);
	returnvector.push_back(sqrt(  (position.x + velocity.x) * (position.x + velocity.x)
								+ (position.y + velocity.y) * (position.y + velocity.y)));
	// + Interceptor's VELOCITY and FACEVECTOR differenct left-right?
	*/
	//cParams::nr0fInputs = returnvector.size();

	return returnvector;
}
