#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "Utilities.h"
#include "RocketHUD.h"
#include <string>


class RocketController : public Object {
public: 
	RocketController() {}
	RocketController(sf::Vector2f position, float angle, std::string ntTexture, std::string ftTexture) : Object(position, Params::nullvec, angle, sf::Vector2f(45, 45), Params::scaleRocket), noThrottleString(ntTexture), fullThrottleString(ftTexture) {
	
		noThrottle.loadFromFile(noThrottleString);
		noThrottle.setSmooth(true);
		noThrottle.setRepeated(false);

		fullThrottle.loadFromFile(fullThrottleString);
		fullThrottle.setSmooth(true);
		fullThrottle.setRepeated(false);

	}
	virtual void update() override;
	virtual void draw(sf::RenderWindow& window) override;

	virtual void controls() = 0;
	
	virtual void TargetHit();

	float throttle = 0.0f;
	void accelerate(float amount);

	void DefineTarget(Object * EnemyRocket);
	Object * LockOnTarget;

	float angular_throttle = 0.0f;
	void angular_accelerate(float amount);
	float angular_velocity = 0.0f;
	
	void CheckForSpin();
	bool SpinAlert = false;

	std::vector<float> NNInputs;

	float prevAngle = angle;
	float rotationalSum = 0.0f;	// for anti spin

protected:
	
	sf::Color color;
	sf::Texture noThrottle;
	std::string noThrottleString;
	sf::Texture fullThrottle;
	std::string fullThrottleString;
};
