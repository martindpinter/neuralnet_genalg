#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

class FlyingObject {
public:

	FlyingObject(sf::Vector2f position, sf::Vector2f velocity, sf::Color color) : position(position), velocity(velocity), color(color) {
		RedRocketTexture_0.loadFromFile("../images/resized_by5/rocket.png");
		RedRocketTexture_1.loadFromFile("../images/resized_by5/rocket_throttle.png");

		RedRocketTexture_0.setSmooth(true); RedRocketTexture_0.setRepeated(false);
		RedRocketTexture_1.setSmooth(true); RedRocketTexture_1.setRepeated(false);
	
	}

	sf::Vector2f position;
	float angle = 0.0f; // 0-360 rads(0-2pi)
	float angular_velocity = 0.0f;
	float throttle = 0.0f;		// 0.0 ... 1.0
	float angular_throttle = 0.0f;
	
	sf::Vector2f velocity;



	sf::Color color;
	void draw(sf::RenderWindow& window);
	void drawRocket(sf::RenderWindow& window);
	sf::Texture RedRocketTexture_0;
	sf::Texture RedRocketTexture_1;
	
	void update(float frametime);

	void accelerate(float amount);
	void angular_accelerate(float amount);
};
