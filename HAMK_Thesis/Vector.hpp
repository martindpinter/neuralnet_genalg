#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Vector {

public:

	Vector() : x(0.0), y(0.0) {}
	Vector(double x, double y) : x(x), y(y) {}

	double x = 0.0;
	double y = 0.0;

	sf::Vector2f to_sfvector();

};
Vector operator + (Vector lhs, Vector rhs);		//itt kell meghivni az operator overloadot