#include "Sandbox.h"
#include "GUI.h"
#include "Utilities.h"

void Sandbox::Run() {
	sf::Clock Clock;

	//bool CollisionDetection = false;
	//bool TargetHit = false;
	
	float PhysicsTimeStepAccumulator = 0.0f;

	while (Window.isOpen()) {
		
		const sf::Time FrameTime = Clock.restart();
		float FrameSeconds = FrameTime.asSeconds();
		fps = 1 / FrameSeconds;
		if (FrameSeconds > 0.1f) FrameSeconds = 0.1f;
		PhysicsTimeStepAccumulator += FrameSeconds;

		HandleUserInput();

		while (PhysicsTimeStepAccumulator >= Params::PhysicsTimeStep) {
			UserRocket.update();
			UserRocket.CheckForSpin();

			PhysicsTimeStepAccumulator -= Params::PhysicsTimeStep;
		}

		Window.clear(sf::Color::Black);
		UserRocket.draw(Window);
		Window.display();
	}
}

void Sandbox::HandleUserInput() {

	sf::Event event;

	while (Window.pollEvent(event)) {

		switch (event.type) {

		case sf::Event::Closed:
			Window.close();
			break;
		case sf::Event::KeyPressed:

			pressedKeys[event.key.code] = true;

			switch (event.key.code) {
			case sf::Keyboard::W:
					
				break;
			case sf::Keyboard::S:

				break;
			case sf::Keyboard::A:

				break;
			case sf::Keyboard::D:

				break;
			case sf::Keyboard::R:
				//UserRocket.reset();
				break;
			case sf::Keyboard::Add:
				if (Params::PhysicsTimeStep >= 0.003)
					Params::PhysicsTimeStep -= (0.1 / Params::PhysicsTimeStepsPerSecond);
				break;
			case sf::Keyboard::Subtract:
				Params::PhysicsTimeStep += (0.1 / Params::PhysicsTimeStepsPerSecond);
				break;
			case sf::Keyboard::Escape:
				Window.close();
				break;
			}
			break;
		}
	}
}