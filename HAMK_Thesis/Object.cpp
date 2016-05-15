#include "Object.h"

bool Object::isOOB() {

	return (position.x > Params::WindowWidth || position.y > Params::WindowHeight || position.x < 0 || position.y < 0);
}