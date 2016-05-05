#pragma once
#include <SFML/Graphics.hpp>
#include <string>
class Params {
public:

	static float pi;

	static int WindowWidth;
	static int WindowHeight;
	static int Framerate;

	static bool GraphicalSimulation;

	static float PhysicsTimeStepsPerSecond;
	static float PhysicsTimeStep;

	// Rocket physics

	static float EnginePower;
	static float RotationalEnginePower;

	static float ConstAirResistance;

	static float NNC_Deadzone;


	static sf::Vector2f posRocketNN;
	static sf::Vector2f posRocketOPP;


	static sf::Vector2f velRocketNN;
	static sf::Vector2f velRocketOPP;


	static float angleRocketNN;
	static float angleRocketOPP;


	/*
	//Rocket visuals
	static const char const* RedRocketNT = "../images/resized_by5/rocket.png";
	static const char const* RedRocketFT = "../images/resized_by5/rocket_throttle.png";

	static const char const* BlueRocketNT = "../images/resized_by5/bluerocket.png";
	static const char const* BlueRocketFT = "../images/resized_by5/bluerocket_throttle.png";
	*/
	static int nr0fInputs;
	static int nr0fOutputs;
	static int nr0fHiddenLayers;
	static int NeuronsPerHiddenLayer;
	static int BiasValue;

	//GenAlg
	static int MaxGenerations;
	static int WeightCount;
	static int PopulationSize;

	static std::string SaveLocation;
	
};