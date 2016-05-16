#include "Bandit.h"
#include <random>
void Bandit::reset(int seed) {

	std::mt19937 gen(seed);
	std::uniform_int_distribution<> disX(Params::WindowWidth * 0.9, Params::WindowWidth * 0.9 + Params::WindowWidth / 10);
	std::uniform_int_distribution<> disY(Params::WindowHeight * 0.1, Params::WindowHeight * 0.1 + Params::WindowHeight * 0.8);

	int randX = disX(gen);
	int randY = disY(gen);
	
	//int randX = rand() % (int(Params::WindowWidth / 10)) + (int(Params::WindowWidth * 0.9));
	//int randY = rand() % (int(Params::WindowHeight * 0.8)) + (int(Params::WindowHeight * 0.1));

	position = sf::Vector2f(randX, randY);
	velocity = Params::nullvec;

	float Egocent_x = LockOnTarget->position.x - position.x;
	float Egocent_y = LockOnTarget->position.y - position.y;
	angle = atan2(Egocent_y, Egocent_x);

	throttle = 0.0f;
	angular_throttle = 0.0f;
	angular_velocity = 0.0f;
	Collided = false;
}

void Bandit::controls() {
	accelerate(0.01f);
}

void Bandit::update() {

	RocketController::update();
	TargetHit();
}