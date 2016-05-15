#include "Target.h"


void Target::reset() {
	position = Params::posTarget;
}

void Target::draw(sf::RenderWindow& Window) {
	Window.draw(Body);
}

void Target::update() {
	position = position;
}
float Target::calcArea() {
	return radius * radius * Params::pi;
}