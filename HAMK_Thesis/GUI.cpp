#include "GUI.h"
#include "Params.h"

void GUI::draw(sf::RenderWindow& Window) {

	sf::Font font;
	sf::Text text;
	std::string GUIString;

	font.loadFromFile("font.ttf");

	text.setFont(font);
	text.setCharacterSize(15);
	text.setColor(sf::Color::White);

	GUIString = "Generation: ";
	GUIString += std::to_string(Generation);
	GUIString += "/";
	GUIString += std::to_string(Params::MaxGenerations);

	GUIString += "\nGenome: ";
	GUIString += std::to_string(Genome);
	GUIString += "/";
	GUIString += std::to_string(Params::PopulationSize);

	GUIString += "\n AvgFit: ";

	text.setString(GUIString);
	text.setPosition(sf::Vector2f(10, 10));

	Window.draw(text);

}