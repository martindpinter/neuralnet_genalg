#include "GraphicalRun.h"
#include "GUI.h"
#include "Utilities.h"
#include "Target.h"
//Object --> RocketController --> RocketNN --> Interceptor
	//						--> Bandit

void GraphicalRun::TopGenomes() {
	sf::Clock Clock;

	SimuTimeInSec = 0.0f;

	float PhysicsTimeStepAccumulator = 0.0f;

	std::vector<sGenome> TopGenomes = LoadTopGenomes();

	for (sGenome& genome : TopGenomes) {
		NN1.feedWeights(genome.value);
		
		I1.reset();
		B1.reset(8);
		TargetB1.reset();
		
		I1.position = genome.initposI1;
		B1.position = genome.initposB1;
		TargetB1.position = genome.initposTargetB1;

		float Egocent_x = TargetB1.position.x - B1.position.x;
		float Egocent_y = TargetB1.position.y - B1.position.y;
		B1.angle = atan2(Egocent_y, Egocent_x);

		while (Window.isOpen()) {
			
			if (I1.Collided || B1.Collided)
				break;

			if (I1.isOOB() && B1.isOOB())
				break;

			const sf::Time FrameTime = Clock.restart();
			float FrameSeconds = FrameTime.asSeconds();
			if (FrameSeconds > 0.1f) FrameSeconds = 0.1f;
			PhysicsTimeStepAccumulator += FrameSeconds;

			while (PhysicsTimeStepAccumulator >= SpeedFactor * Params::PhysicsTimeStep) {

				I1.SetNNControls(&NN1);
				I1.update();
				B1.update();
				TargetB1.update();

				PhysicsTimeStepAccumulator -= SpeedFactor * Params::PhysicsTimeStep;
				SimuTimeInSec += Params::PhysicsTimeStep;
			}


			Window.clear(sf::Color::Black);

			drawBG();
			I1.draw(Window);
			B1.draw(Window);
			TargetB1.draw(Window);

			GUI(Window, iGeneration, iGenome);

			Window.display();
		}
	}
}

void GraphicalRun::ReplayBestGenome() {
	sf::Clock Clock;

	SimuTimeInSec = 0.0f;

	float PhysicsTimeStepAccumulator = 0.0f;

	sGenome BestGenome = LoadBestGenome();

	NN1.feedWeights(BestGenome.value);

	I1.position = BestGenome.initposI1;
	B1.position = BestGenome.initposB1;
	TargetB1.position = BestGenome.initposTargetB1;

	float Egocent_x = TargetB1.position.x - B1.position.x;
	float Egocent_y = TargetB1.position.y - B1.position.y;
	B1.angle = atan2(Egocent_y, Egocent_x);

	while (Window.isOpen()) {
		if (I1.Collided || B1.Collided)
			break;

		if (I1.isOOB() && B1.isOOB())
			break;

		const sf::Time FrameTime = Clock.restart();
		float FrameSeconds = FrameTime.asSeconds();
		if (FrameSeconds > 0.1f) FrameSeconds = 0.1f;
		PhysicsTimeStepAccumulator += FrameSeconds;

		while (PhysicsTimeStepAccumulator >= SpeedFactor * Params::PhysicsTimeStep) {

			I1.SetNNControls(&NN1);
			I1.update();
			B1.update();
			TargetB1.update();

			PhysicsTimeStepAccumulator -= SpeedFactor * Params::PhysicsTimeStep;
			SimuTimeInSec += Params::PhysicsTimeStep;
		}


		Window.clear(sf::Color::Black);

		drawBG();
		I1.draw(Window);
		B1.draw(Window);
		TargetB1.draw(Window);

		GUI(Window, iGeneration, iGenome);

		Window.display();
	}
}

bool GraphicalRun::Simulate(float angle) {

	I1.angle = angle;

	sf::Clock Clock;
	//sf::Clock SimulationClock;

	SimuTimeInSec = 0.0f;

	float PhysicsTimeStepAccumulator = 0.0f;

	NN1.feedWeights(POP1.Genomes[iGenome].value);

	while (Window.isOpen()) {


		if (I1.Collided || B1.Collided)
			break;

		if (I1.isOOB() && B1.isOOB())
			break;


		const sf::Time FrameTime = Clock.restart();
		float FrameSeconds = FrameTime.asSeconds();
		if (FrameSeconds > 0.1f) FrameSeconds = 0.1f;
		PhysicsTimeStepAccumulator += FrameSeconds;

		HandleUserInput();

		while (PhysicsTimeStepAccumulator >= SpeedFactor * Params::PhysicsTimeStep) {

			I1.SetNNControls(&NN1);
			I1.update();
			B1.update();
			TargetB1.update();

			PhysicsTimeStepAccumulator -= SpeedFactor * Params::PhysicsTimeStep;
			SimuTimeInSec += Params::PhysicsTimeStep;
		}


		Window.clear(sf::Color::Black);

		drawBG();
		I1.draw(Window);
		B1.draw(Window);
		TargetB1.draw(Window);

		GUI(Window, iGeneration, iGenome);

		Window.display();
	}
	if (!abort) {
		if (POP1.Genomes[iGenome].fitness == 0)
			POP1.Genomes[iGenome].fitness = I1.calcFitness(SimuTimeInSec);
		else
			POP1.Genomes[iGenome].fitness += I1.calcFitness(SimuTimeInSec);
	}
	abort = false;

	std::cout << "Fitness: " << POP1.Genomes[iGenome].fitness << std::endl;

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
				B1.reset(iGeneration);
				LoadAll();
				abort = true;
				break;
			case sf::Keyboard::Add:
				SpeedFactor *= 1.1f;
				break;
			case sf::Keyboard::Subtract:
				SpeedFactor /= 1.1f;
				break;
			case sf::Keyboard::Escape:
				Window.close();
				break;
			}
			break;
		}
	}
}

void GraphicalRun::drawBG() {
	sf::Texture* BGpointer;
	BGpointer = &BGT;

	sf::Sprite BGSprite;
	BGSprite.setTexture(*BGpointer);
	BGSprite.setPosition(0, 0);

	Window.draw(BGSprite);
}