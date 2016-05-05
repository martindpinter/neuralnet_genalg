#pragma once
#include <SFML/Graphics.hpp>

class RocketController;		//predeklaracio, definiciot nem lat, de pointereket-referenciakat lehet hasznalni. cpp-ben kell includolni a rendes headert

class RocketHUD {
public:
	RocketHUD() {}
	RocketHUD(sf::RenderWindow& Window, RocketController& Rocket) { draw(Window, Rocket); }


	void draw(sf::RenderWindow &Window, RocketController& Rocket);

};