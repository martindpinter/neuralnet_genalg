#include "GraphicalRun.h"
#include "GUI.h"
#include "Utilities.h"

float GraphicalRun::Simulate() {

	sf::Clock Clock;
	sf::Clock SimulationClock;
		
	bool CollisionDetection = false;
	float ClosestDistance = sqrt(pow(Params::WindowHeight, 2) + pow(Params::WindowWidth, 2));
	
	signed LookAtScore = 0;

	

	float PhysicsTimeStepAccumulator = 0.0f;

	while (Window.isOpen() && !CollisionDetection && !OutOfBounds()) {

		const sf::Time FrameTime = Clock.restart();
		float FrameSeconds = FrameTime.asSeconds();
		fps = 1 / FrameSeconds;	// pl. 60 -szor lesz meg benne

		if (FrameSeconds > 0.1f) FrameSeconds = 0.1f;

		PhysicsTimeStepAccumulator += FrameSeconds;

		HandleUserInput();

		while (PhysicsTimeStepAccumulator >= Params::PhysicsTimeStep) {	// PhysicsTimeStep = 1/60	// szive lelke

			Interceptor.SetNNControls(&TheNet);

			Interceptor.update();
			Bandit.update();

			Interceptor.calcLookAtScore(&LookAtScore, &Bandit);

			Interceptor.CheckForSpin();


			CollisionDetection = Interceptor.collision(&Bandit);	//RocketController.cpp

			PhysicsTimeStepAccumulator -= Params::PhysicsTimeStep;
		}


		Window.clear(sf::Color::Black);

		//draw here//
		Interceptor.draw(Window);
		Bandit.draw(Window);
		GUI (Window, iGeneration, iGenome);

		Window.display();
		
	}

	float SimulationTime = SimulationClock.restart().asSeconds();
	
	//std::cout << std::endl << LookAtScore << std::endl;

	if (CollisionDetection) {
		float returnvalue = Sigmoid(Params::MaxSimulationTime - SimulationTime, 5.0) + 1 + (LookAtScore * 0.001);
		
		if (Interceptor.SpinAlert) return returnvalue;
		else return returnvalue + 0.5;
	}
	else {
		float returnvalue = Sigmoid(Params::MaxSimulationTime / (ClosestDistance * SimulationTime)) + (LookAtScore * 0.001);

		if (Interceptor.SpinAlert) return returnvalue - 0.5;
		else return returnvalue;
	}
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
				SaveAll();
				break;
			case sf::Keyboard::L:
				Interceptor.reset();
				Bandit.reset();
				LoadAll();
				break;
			case sf::Keyboard::Add:
				if (Params::PhysicsTimeStep >= 0.003)
					Params::PhysicsTimeStep -= (0.1 / Params::PhysicsTimeStepsPerSecond);
				std::cout << Params::PhysicsTimeStep << std::endl;
				break;
			case sf::Keyboard::Subtract:
				Params::PhysicsTimeStep += (0.1 / Params::PhysicsTimeStepsPerSecond);
				std::cout << Params::PhysicsTimeStep << std::endl;
				break;
			case sf::Keyboard::Escape:
				Window.close();
				break;
			}
			break;
		}
	}
}