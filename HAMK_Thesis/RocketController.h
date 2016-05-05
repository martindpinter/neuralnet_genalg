#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include "RocketHUD.h"
#include <string>


class RocketController {
public: 
	RocketController() {}
	RocketController(sf::Vector2f position, sf::Vector2f velocity, float angle, std::string ntTexture, std::string ftTexture) :
		position(position), velocity(velocity), angle(angle), noThrottleString(ntTexture), fullThrottleString(ftTexture) {
	
		noThrottle.loadFromFile(noThrottleString);
		noThrottle.setSmooth(true);
		noThrottle.setRepeated(false);

		fullThrottle.loadFromFile(fullThrottleString);
		fullThrottle.setSmooth(true);
		fullThrottle.setRepeated(false);

	}

	virtual void controlls() = 0;
	virtual void reset() = 0;

	sf::Vector2f getPosition();
	sf::Vector2f position;	// consider having protected
	sf::Vector2f velocity;	// ...this one too...

	void draw(sf::RenderWindow& window);
	void update();
	void accelerate(float amount);
	void angular_accelerate(float amount);
	sf::Vector2f CalcAirResistance(sf::Vector2f);
	
	bool collision(RocketController *);
	bool OutOfBounds();

	std::vector<float> NNInputs;

	float angle = 0.0f;
	float angular_velocity = 0.0f;
	float throttle = 0.0f;
	float angular_throttle = 0.0f;
	
protected:
	
	sf::Color color;
	sf::Texture noThrottle;
	std::string noThrottleString;
	sf::Texture fullThrottle;
	std::string fullThrottleString;
};
