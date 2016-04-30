#include "cRocketNN.h"
#include "Utilities.h"
#include <SFML/Graphics.hpp>
#include "cRocketRND.h"

void cRocketNN::controlls(float frametime) {

	if (NNControls[0] > 0.4) {
		accelerate(NNControls[0] * frametime);
	}

	if (NNControls[1] < -0.4) {	//jatszogatni
		angular_accelerate((NNControls[1]) * frametime);	// csak pozitivat ad, mindig jobbra fog menni
	}
	if (NNControls[1] > 0.4) {
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

	returnvector.push_back(normalize(VelocityFaceOffset, 0, 2 * cParams::pi));	// check again


	// INPUT 2 :: Celraketa sebessegvektoranak x-tengellyel bezart szoge radianban
	
	float EnemyVelocity_xAxisDegree = atan2(EgocentV_y, EgocentV_x);
	
	float normEVxAD = normalize(EnemyVelocity_xAxisDegree, 0, 2 * cParams::pi);		 

	//normEVxAD = RescaleAtan2(normEVxAD);

	if (normEVxAD < 0) {		// CSUNYAVAGYNAGYON :(((((((
		normEVxAD += 1;
	}


	returnvector.push_back(normEVxAD);
	

	// INPUT 3 :: Celraketa iranya az elfogohoz kepest (Left 1.0 ... [Centre-> 0.5 <-Centre] ... 0.0 Right)
	
	float RelativeAngle = atan2(Egocent_y, Egocent_x);	//	Angle of incoming rocket relative to the interceptor's x axis in radians

	//RelativeAngle = fmod(RelativeAngle, 2 * cParams::pi);	// NOT SURE IF NECCESSARY

	float Difference = angle - RelativeAngle; // talan itt van elasva...

	float normDifference = normalize(Difference, 0, 2 * cParams::pi);		// STILL NEEDS REWORKING (changed pi's coefficient from 2 to 4 to have 0.5 as centre)
	
	normDifference = RescaleAtan2(normDifference);


	//std::cout << "Normalized Difference is " << normDifference << std::endl;

	returnvector.push_back(normDifference);

	//cParams::nr0fInputs = returnvector.size();

	return returnvector;
}
