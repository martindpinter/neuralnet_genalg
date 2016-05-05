#pragma once
#include <SFML/Graphics.hpp>

class GUI {
public:
	GUI(sf::RenderWindow& Window, int Generation, int Genome) : Generation(Generation), Genome(Genome) { draw(Window);  }

	int Generation;
	int Genome;



	void draw(sf::RenderWindow& Window);
};