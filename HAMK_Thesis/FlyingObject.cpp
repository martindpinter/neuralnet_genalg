#include "FlyingObject.hpp"
#include <iostream>

void FlyingObject::drawRocket(sf::RenderWindow & window) {
	
	float pi = 3.141592f;

	sf::Texture* rocketTexture;
	
	if (throttle == 0.0f) {
		rocketTexture = & RedRocketTexture_0;
	}
	else {
		rocketTexture = & RedRocketTexture_1;
	}
	
	sf::Sprite rocketSprite;
	rocketSprite.setTexture(*rocketTexture);
	rocketSprite.setPosition(position);
	rocketSprite.setRotation((angle + pi / 2) * (180.0f / pi));
	rocketSprite.setOrigin(19, 27);

	window.draw(rocketSprite);
}
void FlyingObject::draw(sf::RenderWindow & window) {
	
	drawRocket(window);
}

void FlyingObject::update(float frametime) {

	const float engine_power = 10.0f;
	const float rotational_engine_power = 0.6f;

	float angular_acceleration = angular_throttle * rotational_engine_power;
	angular_velocity += angular_acceleration * frametime;
	angle += angular_velocity * frametime;


	sf::Vector2f acceleration(cos(angle), sin(angle));
	acceleration *= throttle * engine_power;	//ha throttle 0, 0vektorra zsugorul
	velocity += acceleration * frametime;
	position += velocity * frametime;
	
}



void FlyingObject::accelerate(float amount) {
	
	throttle += amount;
	throttle = clamp(throttle, -1.0f, 1.0f);
}

void FlyingObject::angular_accelerate(float alpha_amount) {
		
	angular_throttle += alpha_amount;
	angular_throttle = clamp(angular_throttle, -1.0, 1.0);
}