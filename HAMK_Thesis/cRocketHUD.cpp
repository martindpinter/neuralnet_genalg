#include <iostream>
#include "cRocketHUD.h"
#include "cRocketController.h"

void cRocketHUD::draw(sf::RenderWindow &window, cRocketController& Rocket) {

	//draw lines
	sf::RectangleShape line1(sf::Vector2f(25, 2));
	sf::RectangleShape line2(sf::Vector2f(25, 2));
	
	line1.setPosition(Rocket.position + sf::Vector2f(15, 15));

	sf::Font font;
	sf::Text text;
	std::string HUDString;

	font.loadFromFile("font.ttf");

	text.setFont(font);
	text.setCharacterSize(15);
	text.setColor(sf::Color::White);
	
	line1.rotate(60);
	line2.rotate(90);

	window.draw(line1);
	window.draw(line2);
	//draw name


	//draw position
	HUDString = "";
	HUDString += "x = ";
	HUDString += std::to_string(Rocket.position.x);
	HUDString += "\ny = ";
	HUDString += std::to_string(Rocket.position.y);

	HUDString += "\nAngle = ";
	HUDString += std::to_string(rad2deg(Rocket.angle));
	
	HUDString += "\nVelocity = ";
	HUDString += std::to_string(sqrt(pow(Rocket.velocity.x, 2) + pow(Rocket.velocity.y, 2)));
	
	//draw velocity

	text.setString(HUDString);
	text.setPosition(Rocket.position + sf::Vector2f(32, 32));
	window.draw(text);
}