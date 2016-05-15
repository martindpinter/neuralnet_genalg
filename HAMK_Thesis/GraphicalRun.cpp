#include "GraphicalRun.h"
#include "GUI.h"
#include "Utilities.h"
#include "Target.h"

bool GraphicalRun::Simulate() {

	sf::Clock Clock;
	//sf::Clock SimulationClock;

	SimuTimeInSec = 0.0f;

	float PhysicsTimeStepAccumulator = 0.0f;

	NN1.feedWeights(POP1.Genomes[iGenome].value);
	NN2.feedWeights(POP2.Genomes[iGenome].value);

	while (Window.isOpen()) {


		if (I1.Collided || B1.Collided)
			break;

		if (I1.isOOB() && B1.isOOB())
			break;

		if (SimuTimeInSec >= Params::MaxSimulationTime)
			break;

		const sf::Time FrameTime = Clock.restart();
		float FrameSeconds = FrameTime.asSeconds();
		if (FrameSeconds > 0.1f) FrameSeconds = 0.1f;
		PhysicsTimeStepAccumulator += FrameSeconds;

		HandleUserInput();

		while (PhysicsTimeStepAccumulator >= SpeedFactor * Params::PhysicsTimeStep) {

			I1.SetNNControls(&NN1);
			I1.update();

			B1.SetNNControls(&NN2);
			B1.update();

			PhysicsTimeStepAccumulator -= SpeedFactor * Params::PhysicsTimeStep;
			SimuTimeInSec += SpeedFactor * Params::PhysicsTimeStep;
		}


		Window.clear(sf::Color::Black);


		I1.draw(Window);
		B1.draw(Window);
		City.draw(Window);

		GUI(Window, iGeneration, iGenome);
		std::cout << SimuTimeInSec << std::endl;
		Window.display();
	}
	if (!abort) {
		POP1.Genomes[iGenome].fitness = I1.calcFitness(SimuTimeInSec);
		POP2.Genomes[iGenome].fitness = B1.calcFitness(SimuTimeInSec);
	}
	abort = false;

	return !Window.isOpen();

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
				I1.reset();
				B1.reset();
				LoadAll();
				abort = true;
				break;
			case sf::Keyboard::Add:
				SpeedFactor *= 1.1f;
				std::cout << Params::PhysicsTimeStep << std::endl;
				break;
			case sf::Keyboard::Subtract:
				SpeedFactor /= 1.1f;
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