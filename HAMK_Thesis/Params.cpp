#include "Params.h"

float Params::pi = 3.1415926535;

const sf::Vector2f Params::nullvec = sf::Vector2f(0, 0);

// Render properties
int Params::WindowWidth = 1200;
int Params::WindowHeight = 600;
int Params::Framerate = 60;

bool Params::GraphicalSimulation = true;

int Params::MaxSimulationTime = 5;

//Qtsma
float Params::PhysicsTimeStepsPerSecond = 60;	//64 for Qtsma
float Params::PhysicsTimeStep = 1.0f / PhysicsTimeStepsPerSecond;

// Rocket physics
float Params::EnginePower = 1.0f;				// const? 
float Params::RotationalEnginePower = 0.015f;	// const?

float Params::ConstAirResistance = 0.003;
float Params::Friction = 0.8;

float Params::NNC_Deadzone = 0.15;	//	This value determines the deadzone for Left-Right controls of the Neural Net.

std::string Params::BackgroundTexture = "../images/background.png";

std::string Params::BlueNTT = "../images/resized_by5/BlueNT.png";
std::string Params::BlueFTT = "../images/resized_by5/BlueFT.png";
std::string Params::RedNTT = "../images/resized_by5/RedNT.png";
std::string Params::RedFTT = "../images/resized_by5/RedFT.png";

std::string Params::TargetT = "../images/TargetT.png";

// Initial positions of the rockets
sf::Vector2f Params::posRocketNN = sf::Vector2f(50, Params::WindowHeight - 50);
sf::Vector2f Params::posRocketOPP = sf::Vector2f(Params::WindowWidth - 150, Params::WindowHeight - 100);
sf::Vector2f Params::posRocketHC = sf::Vector2f(Params::WindowWidth / 2, Params::WindowHeight * 3 / 4);
sf::Vector2f Params::posRocketDMM = sf::Vector2f(Params::WindowWidth - 150, Params::WindowHeight - 100);

float Params::scaleRocket = 0.2;
float Params::scaleTarget = 0.132;

sf::Vector2f Params::posTarget = sf::Vector2f(Params::WindowWidth / 10, Params::WindowHeight / 2);
float Params::radTarget = 75;

float Params::angleRocketNN = 0.75 * pi;
float Params::angleRocketOPP = pi;
float Params::angleRocketHC = 1.5 * pi;
float Params::angleRocketDMM = 0;
float Params::angleTarget = 0;

/* Neural Net Specifications */
int Params::nr0fInputs = 5;
int Params::nr0fOutputs = 2;
int Params::nr0fHiddenLayers = 1;
int Params::NeuronsPerHiddenLayer = 6;

int Params::WeightCount = nr0fInputs * NeuronsPerHiddenLayer 
						 + (pow(NeuronsPerHiddenLayer, (nr0fHiddenLayers - 1))) * (nr0fHiddenLayers -1)
						 + nr0fOutputs * NeuronsPerHiddenLayer
						 + (NeuronsPerHiddenLayer * nr0fHiddenLayers + nr0fOutputs);			
// akar meg is lehet szamoltatni

int Params::MaxGenerations = 1000000;

int Params::BiasValue = 1.0f;

int Params::PopulationSize = 100;

//nr0finputs * neuronsperhiddenlayer + nr0fhiddenlayers * neuronsperhiddenlayer^2

std::string Params::SaveLocation = "./Save/";
