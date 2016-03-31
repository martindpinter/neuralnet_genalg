#include "cParams.h"
float cParams::pi = 3.141592;
// Render properties
int cParams::WindowWidth = 800;
int cParams::WindowHeight = 600;
int cParams::Framerate = 60;

// Rocket physics
float cParams::EnginePower = 10.0f;				// const? 
float cParams::RotationalEnginePower = 0.6f;	// const?

// Initial positions of the rockets
sf::Vector2f cParams::posRocketNN = sf::Vector2f(100, 400);
sf::Vector2f cParams::posRocketOPP = sf::Vector2f(250, 400);

/* Initial velocities of the rocket */
sf::Vector2f cParams::velRocketNN = sf::Vector2f(0, 0);
sf::Vector2f cParams::velRocketOPP = sf::Vector2f(-2, 0);

float cParams::angleRocketNN = 1.5 * cParams::pi;
float cParams::angleRocketOPP = pi;

/* Neural Net Specifications */
int cParams::nr0fInputs = 5;
int cParams::nr0fOutputs = 2;
int cParams::nr0fHiddenLayers = 1;
int cParams::NeuronsPerHiddenLayer = 6;

int cParams::WeightCount = nr0fInputs * NeuronsPerHiddenLayer 
						 + (pow(NeuronsPerHiddenLayer, (nr0fHiddenLayers - 1))) * (nr0fHiddenLayers -1)
						 + nr0fOutputs * NeuronsPerHiddenLayer;			// akar meg is lehet szamoltatni

int cParams::PopulationSize = 100;

//nr0finputs * neuronsperhiddenlayer + nr0fhiddenlayers * neuronsperhiddenlayer^2
