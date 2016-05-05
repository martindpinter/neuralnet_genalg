#include "GraphicalRun.h"
#include "GUI.h"

float GraphicalRun::Simulate() {

	sf::Clock SimulationClock;
		
	bool CollisionDetection = false;

	float ClosestDistance = sqrt(pow(Params::WindowHeight, 2) + pow(Params::WindowWidth, 2));


	sf::Clock Clock;

	float PhysicsTimeStepAccumulator = 0.0f;

	while (Window.isOpen() && !CollisionDetection && !OutOfBounds()) {

		const sf::Time FrameTime = Clock.restart();
		float FrameSeconds = FrameTime.asSeconds();
		fps = 1 / FrameSeconds;	// pl. 60 -szor lesz meg benne

		if (FrameSeconds > 0.1f) {
			FrameSeconds = 0.1f;
		}

		PhysicsTimeStepAccumulator += FrameSeconds;

		while (PhysicsTimeStepAccumulator >= Params::PhysicsTimeStep) {	// PhysicsTimeStep = 1/60

			Interceptor.SetNNControls(&TheNet);

			HandleUserInput();

			Interceptor.update();	//frametimet kivenni
			Bandit.update();


			CollisionDetection = Interceptor.collision(&Bandit);	//RocketController.cpp

			PhysicsTimeStepAccumulator -= Params::PhysicsTimeStep;
		}


		Window.clear(sf::Color::Black);

		//draw here//
		Interceptor.draw(Window);
		Bandit.draw(Window);
		GUI (Window, iGeneration, iGenome);

		Window.display();
		if (fpsLimit > 0) {
			const sf::Time RenderTime = Clock.getElapsedTime();
			if (RenderTime.asSeconds() < 1.0f / fpsLimit) {
				sf::sleep(sf::seconds(1.0f / fpsLimit - RenderTime.asSeconds()));
			}
		}
	}

	float SimulationTime = SimulationClock.restart().asSeconds();

	return (CollisionDetection * (1 - SimulationTime / 10) + !CollisionDetection * (1 / ClosestDistance * SimulationTime));
}

void GraphicalRun::HandleUserInput() {

	sf::Event event;

	while (Window.pollEvent(event)) {
		
		switch (event.type) {
		
		case sf::Event::Closed:
			Window.close();
			break;
		case sf::Event::KeyPressed:
			
			pressedKeys[event.key.code] = true;
			
			switch (event.key.code) {
			case sf::Keyboard::S:
				Save();
				break;
			case sf::Keyboard::L:
				Load();
				break;
			case sf::Keyboard::Escape:
				Window.close();
				break;
			}
			break;
		}
	}
}