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
	cRocketHUD HUD(window, *this);
}

void cRocketController::update(float frametime) {

	float angular_acceleration = angular_throttle * cParams::RotationalEnginePower;

	controlls(frametime);		// event poll here

	angular_velocity += angular_acceleration * frametime;
	angular_velocity = clamp(angular_velocity, -0.4f, 0.4f);

	
	angle += angular_velocity * frametime;
	
	angle = fmod(angle, 2*cParams::pi);

	sf::Vector2f acceleration(cos(angle), sin(angle));
	acceleration *= throttle * cParams::EnginePower;	//ha a throttle 0, 0vektorra zsugorul
	
	acceleration = CalcAirResistance(acceleration);
	
	
	velocity += acceleration * frametime;
	position += velocity * frametime;
}

void cRocketController::accelerate(float amount) {

	throttle += amount;
	throttle = clamp(throttle, 0.0f, 1.0f);
}

void cRocketController::angular_accelerate(float alpha_amount) {
	angular_throttle = alpha_amount;	// Originally += 
	angular_throttle = clamp(angular_throttle, -1.0, 1.0);
}

sf::Vector2f cRocketController::CalcAirResistance(sf::Vector2f acceleration)
{
	acceleration.x -= cParams::ConstAirResistance * velocity.x * velocity.x;	// air resistance
	acceleration.y -= cParams::ConstAirResistance * velocity.y * velocity.y;

	return acceleration;
}
