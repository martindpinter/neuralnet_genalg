#include "Vector.hpp"


sf::Vector2f Vector::to_sfvector() {
	
	return sf::Vector2f(x, y);
}

Vector operator + (Vector lhs, Vector rhs) {
	lhs.x += rhs.x;
	lhs.y += rhs.y;

	return (lhs);
}