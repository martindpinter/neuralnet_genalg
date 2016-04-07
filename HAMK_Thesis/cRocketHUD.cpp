#include "cRocketHUD.h"
#include "cRocketController.h"

void cRocketHUD::draw(sf::RenderWindow &window, cRocketController& Rocket) {

	//draw lines
	sf::RectangleShape line1(sf::Vector2f(25, 2));
	sf::RectangleShape line2(sf::Vector2f(25, 2));
	
	line1.setPosition(Rocket.position + sf::Vector2f(15, 15));

	
	line1.rotate(60);
	line2.rotate(90);

	window.draw(line1);
	window.draw(line2);
	//draw name


	//draw position


	//draw velocity



}