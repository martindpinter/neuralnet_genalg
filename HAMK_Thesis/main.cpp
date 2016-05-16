#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "PerformanceRun.h"
#include "GraphicalRun.h"
#include "Sandbox.h"

#define PI 3.141592;


int main() {
	
	srand(time(nullptr));

	std::cout << "MENU" << std::endl;
	std::cout << "1. Start New Performance Teaching" << std::endl;
	std::cout << "2. Continue Performance Teaching" << std::endl;
	std::cout << "3. Graphical Simulation" << std::endl;
	std::cout << "4. Sandbox Mode" << std::endl;
	std::cout << "5. Replay Best Genome" << std::endl;
	std::cout << "6. Top Genomes" << std::endl;
	std::cout << "X. Quit Program" << std::endl;
	

	bool quit = false;

	while (!quit) {

		char menuChoice;
		std::cin >> menuChoice;

		if (menuChoice == '1') {
			PerformanceRun GM;
			GM.Run();
		}
		else if (menuChoice == '2') {
			PerformanceRun GM;
			GM.LoadAll();
			GM.Run();

		}
		else if (menuChoice == '3') {
			GraphicalRun GM;
			GM.LoadAll();
			GM.Run();
		}
		else if (menuChoice == '4') {
			Sandbox GM;
			GM.Run();
		}
		else if (menuChoice == '5') {
			GraphicalRun GM;
			GM.ReplayBestGenome();
			//char endchar;
			//std::cin >> endchar;
		}
		else if (menuChoice == '6') {
			GraphicalRun GM;
			GM.TopGenomes();
		}
		else if (menuChoice == 'x') {
			quit = true;
		}
	}

	return 0;
}

