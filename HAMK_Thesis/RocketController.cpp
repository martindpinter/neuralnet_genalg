#include "RocketController.h"
#include "Params.h"
#include <iostream>	// don't forget to remove

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

	controls();		// event poll here

	angular_velocity += angular_acceleration;
	angular_velocity = clamp(angular_velocity, -0.4f, 0.4f);
	angular_velocity *= Params::Friction;

	prevAngle = angle;
	angle += angular_velocity;
	
	rotationalSum += angle - prevAngle;

	if (angle < 0)
		angle = 2 * Params::pi + angle;

	angle = std::fmod(angle, 2 * Params::pi);

	sf::Vector2f acceleration(cos(angle), sin(angle));
	acceleration *= throttle * Params::EnginePower;	//ha a throttle 0, 0vektorra zsugorul

	velocity += acceleration;
	velocity *= Params::Friction;
	position += velocity;
}


void RocketController::accelerate(float amount) {

	throttle += amount;
	throttle = clamp(throttle, 0.0f, 1.0f);
}

void RocketController::angular_accelerate(float alpha_amount) {
	
	if (angular_throttle > 0 && alpha_amount < 0) { alpha_amount *= 3; }
	if (angular_throttle < 0 && alpha_amount > 0) { alpha_amount *= 3; }

	angular_throttle += alpha_amount;
	angular_throttle = clamp(angular_throttle, -1.0, 1.0);
}

void RocketController::CheckForSpin() {
	if (SpinAlert == false) {
		if (rotationalSum >= Params::pi) SpinAlert = true;
		else if (rotationalSum <= -1 * Params::pi) SpinAlert = true;
	}
}
