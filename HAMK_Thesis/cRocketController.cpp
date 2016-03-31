#include "cRocketController.h"
#include "cParams.h"

sf::Vector2f cRocketController::getPosition() {
	return position;
}

bool cRocketController::OutOfBounds() {
	if (position.x > cParams::WindowWidth || position.y > cParams::WindowHeight || position.x < 0 || position.y < 0)
		return true;
	else
		return false;
}

bool cRocketController::collision(cRocketController * otherRocket) {

	float dx = position.x - otherRocket->position.x;
	float dy = position.y - otherRocket->position.y;
	float distance = sqrt(dx * dx + dy * dy);

	return distance < (20 + 20);
}

void cRocketController::draw(sf::RenderWindow& window) {
	float pi = 3.141592f;

	sf::Texture* rocketTexture;

	if (throttle == 0.0f) {
		rocketTexture = &noThrottle;
	}
	else {
		rocketTexture = &fullThrottle;
	}

	sf::Sprite rocketSprite;
	rocketSprite.setTexture(*rocketTexture);
	rocketSprite.setPosition(position);
	rocketSprite.setRotation((angle + pi / 2) * (180.0f / pi));
	rocketSprite.setOrigin(19, 27);

	window.draw(rocketSprite);
}

void cRocketController::update(float frametime) {

	float angular_acceleration = angular_throttle * cParams::RotationalEnginePower;

	controlls(frametime);		// event poll here

	angular_velocity += angular_acceleration * frametime;
	angle += angular_velocity * frametime;

	sf::Vector2f acceleration(cos(angle), sin(angle));
	acceleration *= throttle * cParams::EnginePower;	//ha a throttle 0, 0vektorra zsugorul
	velocity += acceleration * frametime;
	position += velocity * frametime;
}

void cRocketController::accelerate(float amount) {

	throttle += amount;
	throttle = clamp(throttle, -1.0f, 1.0f);
}

void cRocketController::angular_accelerate(float alpha_amount) {
	angular_throttle += alpha_amount;
	angular_throttle = clamp(angular_throttle, -1.0, 1.0);
}
/*
std::vector<float> cRocketController::GetNNInputs(cRocketController & EnemyRocket) {
	
	std::vector<float> returnvector;


	// INPUT 1 :: Sebessegvektor hossza
	float VelocityVectorLength = sqrt(pow(velocity.x, 2) + pow(velocity.y, 2));
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(VelocityVectorLength);


	// INPUT 2 :: Facevector es sebessegvector iranyanak kulonbsege
	float VeloVec_xAxisDegree = rad2deg(atan2(velocity.y, velocity.x));
	float FaceVec_xAxisDegree = rad2deg(angle);

	float VelocityFaceOffset = abs(VeloVec_xAxisDegree - FaceVec_xAxisDegree);
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(VelocityFaceOffset);


	// INPUT 3 :: Celraketa sebessegvektora.x
	float EnemyVeloVec_x = EnemyRocket.velocity.x;
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(EnemyVeloVec_x);


	// INPUT 4 :: Celraketa sebessegvektora.y
	float EnemyVelovec_y = EnemyRocket.velocity.y;
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(EnemyVelovec_y);


	// INPUT 5 :: Celraketa iranya az elfogohoz kepest (Left -1.0 ... +1.0 Right)
	float Egocent_x = EnemyRocket.position.x - position.x;
	float Egocent_y = EnemyRocket.position.y - position.y;
	float RelativeAngle = atan2(Egocent_y, Egocent_x);

	float direction = RelativeAngle / 2 * 3.141592;
	//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	returnvector.push_back(direction);

	return returnvector;
}*/
