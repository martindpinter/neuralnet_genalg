#pragma once
#include <SFML/Graphics.hpp>
#include "Params.h"
#include "Object.h"

class Target : public Object {
public:
	Target() : Target(Params::posTarget, Params::radTarget, sf::Vector2f(150.0f, 150.0f), Params::scaleTarget) {}

	Target(sf::Vector2f position, float radius, sf::Vector2f size, float scale) : Object(position, Params::nullvec, Params::angleTarget, size, scale), radius(radius), TextureString(Params::TargetT) {
		
		
		BodyTexture.loadFromFile(TextureString);
		BodyTexture.setSmooth(true);
		BodyTexture.setRepeated(false);
	
	}

	float calcArea();

	void reset();
	virtual void draw(sf::RenderWindow&) override;
	virtual void update() override;

	bool randomized = true;
	
	sf::Texture BodyTexture;
	sf::Sprite BodySprite;
	std::string TextureString;

	float radius;
	sf::CircleShape Body;
	sf::Color Color = sf::Color::Green;
};