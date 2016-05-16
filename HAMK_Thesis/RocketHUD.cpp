#include <iostream>
#include "RocketHUD.h"
#include "RocketController.h"
#include "Utilities.h"
#include "Params.h"
void RocketHUD::draw(sf::RenderWindow& Window, RocketController& Rocket) {
	bool attached = true;
	//draw lines
	if (attached) {

		sf::RectangleShape line(sf::Vector2f(25, 2));

		line.setPosition(Rocket.position + sf::Vector2f(15, 15));

		line.rotate(60);
		Window.draw(line);
	}


	
	//draw info
	sf::Font font;
	sf::Text text;
	std::string HUDString;

	font.loadFromFile("font.ttf");

	text.setFont(font);
	text.setCharacterSize(15);
	text.setColor(sf::Color::White);

	HUDString = "";
	/*HUDString += "x = ";
	HUDString += std::to_string(Rocket.position.x);
	HUDString += "\ny = ";
	HUDString += std::to_string(Rocket.position.y);
	*/
	HUDString += "\nAngle = ";
	HUDString += std::to_string(Rocket.angle);
	
	HUDString += "\n";

	HUDString += "\nThrottle = ";
	HUDString += std::to_string(Rocket.throttle);

	HUDString += "\nvelocity = ";
	HUDString += std::to_string(sqrt(pow(Rocket.velocity.x, 2) + pow(Rocket.velocity.y, 2)));

	/*HUDString += "\n";

	HUDString += "\nAngularThrottle = ";
	HUDString += std::to_string(Rocket.angular_throttle);

	HUDString += "\nAngularvelocity = ";
	HUDString += std::to_string(Rocket.angular_velocity);

	HUDString += "\n";

	HUDString += "\nRotaSum = ";
	HUDString += std::to_string(Rocket.rotationalSum);*/

	//draw velocity

	text.setString(HUDString);

	if (attached) {
		//text.setPosition(Rocket.position + sf::Vector2f(32, 32));
		text.setPosition(Rocket.position + sf::Vector2f(32, 0));
	}
	else {
		text.setPosition(sf::Vector2f( 100, 25));
	}


	Window.draw(text);
}