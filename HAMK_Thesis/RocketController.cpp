#include "RocketController.h"
#include "Params.h"
#include <iostream>	// don't forget to remove

sf::Vector2f RocketController::getPosition() {
	return position;
}

bool RocketController::OutOfBounds() {
	if (position.x > Params::WindowWidth || position.y > Params::WindowHeight || position.x < 0 || position.y < 0)
		return true;
	else
		return false;
}


//Celraketa iranya az elfogohoz kepest(Left 0.0 ...[Centre-> 0.5 <-Centre] ... 1.0 Right)
float RocketController::LookAt(RocketController* EnemyRocket) {

	float Egocent_x = EnemyRocket->position.x - position.x;
	float Egocent_y = EnemyRocket->position.y - position.y;
	
	float Angle_reltoX = atan2(Egocent_y, Egocent_x);
	float Difference = 2 * Params::pi - angle - Angle_reltoX;

	float normDifference = normalize(Difference, -1 * Params::pi, 1 * Params::pi);

	return normDifference;

}

bool RocketController::collision(RocketController * otherRocket) {

	float dx = position.x - otherRocket->position.x;
	float dy = position.y - otherRocket->position.y;
	float distance = sqrt(dx * dx + dy * dy);

	return distance < (20 + 20);
}

void RocketController::draw(sf::RenderWindow& window) {

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
	rocketSprite.setRotation((angle + Params::pi / 2) * (180.0f / Params::pi));
	rocketSprite.setOrigin(19, 27);

	window.draw(rocketSprite);
	RocketHUD HUD(window, *this);
}

void RocketController::update() {

	float angular_acceleration = angular_throttle * Params::RotationalEnginePower;

	controlls();		// event poll here

	angular_velocity += angular_acceleration;
	angular_velocity = clamp(angular_velocity, -0.4f, 0.4f);

	prevAngle = angle;

	angle += angular_velocity;
	
	rotationalSum += angle - prevAngle;

	if (angle < 0)
		angle = 2 * Params::pi + angle;

	angle = std::fmod(angle, 2 * Params::pi);




	sf::Vector2f acceleration(cos(angle), sin(angle));
	acceleration *= throttle * Params::EnginePower;	//ha a throttle 0, 0vektorra zsugorul

	acceleration = CalcAirResistance(acceleration);


	velocity += acceleration;
	position += velocity;
}


void RocketController::accelerate(float amount) {

	throttle += amount;
	throttle = clamp(throttle, 0.0f, 1.0f);
}

void RocketController::angular_accelerate(float alpha_amount) {
	angular_throttle = alpha_amount;	// Originally += 
	angular_throttle = clamp(angular_throttle, -1.0, 1.0);
}

sf::Vector2f RocketController::CalcAirResistance(sf::Vector2f acceleration)
{
	acceleration.x -= Params::ConstAirResistance * velocity.x * velocity.x;	// air resistance
	acceleration.y -= Params::ConstAirResistance * velocity.y * velocity.y;

	return acceleration;
}

float RocketController::calcLookAtScore(signed * LookAtScore, RocketController * EnemyRocket) {
	
	float LookAtEnemy = LookAt(EnemyRocket);

	if (LookAtEnemy > 0.48 && LookAtEnemy < 0.52)
		LookAtScore++;
	else
		LookAtScore--;


	return 0.0f;
}

void RocketController::CheckForSpin() {
	if (SpinAlert == false) {
		if (rotationalSum >= Params::pi) SpinAlert = true;
		else if (rotationalSum <= -1 * Params::pi) SpinAlert = true;
	}
}
