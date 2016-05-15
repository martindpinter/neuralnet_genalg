#pragma once
#include <SFML/Graphics.hpp>
#include "Params.h"
#include "Object.h"

class Target : public Object {
public:
	Target() : Target(Params::posTarget, 40) {}

	Target(sf::Vector2f position, float radius) : Object(position, Params::nullvec, angle), radius(radius) {
		
		Body.setFillColor(Color);
		Body.setPosition(position);
		Body.setRadius(radius);


	}

	float calcArea();

	virtual void reset() override;
	virtual void draw(sf::RenderWindow&) override;
	virtual void update() override;

private:
	
	float radius;
	sf::CircleShape Body;
	sf::Color Color = sf::Color::Green;
};