#include "cParams.h"
float cParams::pi = 3.1415926535;
// Render properties
int cParams::WindowWidth = 1200;
int cParams::WindowHeight = 600;
int cParams::Framerate = 60;

// Rocket physics
float cParams::EnginePower = 0.2f;				// const? 
float cParams::RotationalEnginePower = 0.003f;	// const?

float cParams::ConstAirResistance = 0.0000003;

float cParams::NNC_Deadzone = 0.15;	//	This value determines the deadzone for Left-Right controls of the Interceptor.

// Initial positions of the rockets
//sf::Vector2f cParams::posRocketNN = sf::Vector2f(WindowWidth / 5, WindowHeight - WindowHeight / 3);
//sf::Vector2f cParams::posRocketOPP = sf::Vector2f(WindowWidth - WindowWidth / 10, WindowHeight / 10);

sf::Vector2f cParams::posRocketNN = sf::Vector2f(100, 400);
sf::Vector2f cParams::posRocketOPP = sf::Vector2f(500, 400);


/* Initial velocities of the rocket */
sf::Vector2f cParams::velRocketNN = sf::Vector2f(0, 0);
sf::Vector2f cParams::velRocketOPP = sf::Vector2f(0, -3);

float cParams::angleRocketNN = 1.75 * pi;
float cParams::angleRocketOPP = pi;

/* Neural Net Specifications */
int cParams::nr0fInputs = 4;
int cParams::nr0fOutputs = 2;
int cParams::nr0fHiddenLayers = 1;
int cParams::NeuronsPerHiddenLayer = 6;

int cParams::WeightCount = nr0fInputs * NeuronsPerHiddenLayer 
						 + (pow(NeuronsPerHiddenLayer, (nr0fHiddenLayers - 1))) * (nr0fHiddenLayers -1)
						 + nr0fOutputs * NeuronsPerHiddenLayer
						 + (NeuronsPerHiddenLayer * nr0fHiddenLayers + nr0fOutputs);			
// akar meg is lehet szamoltatni

int cParams::BiasValue = 1.0f;

int cParams::PopulationSize = WeightCount;

//nr0finputs * neuronsperhiddenlayer + nr0fhiddenlayers * neuronsperhiddenlayer^2
