#pragma once
#include <SFML/Graphics.hpp>
#include "Params.h"

class Object {
public:

	Object() {}
	Object(sf::Vector2f position, sf::Vector2f velocity, float angle) : position(position), velocity(velocity), angle(angle) {}

	virtual void reset() = 0;
	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update() = 0;

	enum Type { Target, Rocket };

	sf::Vector2f position;
	sf::Vector2f velocity;
	
	float angle = 0;

	bool Collided = false;

	bool isOOB();


};