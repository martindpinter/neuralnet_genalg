#include "Target.h"
#include <iostream>


void Target::reset() {
	

	int randX = rand() % (int(Params::WindowWidth / 10)) + (int(Params::WindowWidth * 0.05));
	int randY = rand() % (int(Params::WindowHeight * 0.8)) + (int(Params::WindowHeight * 0.1));

	//Body.setPosition(sf::Vector2f(randX, randY));
	position = sf::Vector2f(randX, randY);
}

void Target::draw(sf::RenderWindow& Window) {

	sf::Texture* TargetTpointer;
	TargetTpointer = &BodyTexture;

	BodySprite.setTexture(*TargetTpointer);
	BodySprite.setPosition(position);
	BodySprite.setOrigin(Params::radTarget, Params::radTarget);

	BodySprite.setScale(Params::scaleTarget, Params::scaleTarget);

	Window.draw(BodySprite);
}

void Target::update() {
	BodySprite.setPosition(position);
	BodySprite.setOrigin(Params::radTarget / 2, Params::radTarget / 2);
}

float Target::calcArea() {
	return radius * radius * Params::pi;
}