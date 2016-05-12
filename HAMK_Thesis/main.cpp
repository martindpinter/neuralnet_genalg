#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "PerformanceRun.h"
#include "GraphicalRun.h"
#include "Sandbox.h"

#define PI 3.141592;


int main() {
	
	srand(time(nullptr));

	std::cout << "MENU" << std::endl;
	std::cout << "1. Console Simulation" << std::endl;
	std::cout << "2. Graphical Simulation" << std::endl;
	std::cout << "3. Sandbox Mode" << std::endl;
	
	char menuChoice;
	std::cin >> menuChoice;


	if (menuChoice == '1') {
		PerformanceRun GM;
		//GM.LoadAll();
		GM.Run();
	}
	if (menuChoice == '2') {
		GraphicalRun GM;
		GM.Run();
	}
	if (menuChoice == '3') {
		Sandbox GM;
		GM.Run();
	}
	

	return 0;
}

