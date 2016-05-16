#pragma once
#include <SFML/Graphics.hpp>
#include "Params.h"

class Object {
public:

	Object() {}
	Object(sf::Vector2f position, sf::Vector2f velocity, float angle, sf::Vector2f size, float scale) : position(position), velocity(velocity), angle(angle), size(size), scale(scale) {
	
	
	}

	virtual void draw(sf::RenderWindow& window) = 0;
	virtual void update() = 0;

	enum Type { Target, Rocket };

	sf::Vector2f position;
	sf::Vector2f velocity;
	
	float angle = 0;

	//sf::FloatRect boundingBox;
	sf::FloatRect getBoundingBox();
	float scale;
	sf::Vector2f size;

	bool Collided = false;

	bool isOOB();


};