#include "UserInterface.h"

UserInterface::UserInterface() {}
UserInterface::~UserInterface() {}

void UserInterface::Run() {
	Controller controller;
	bool running = true;
	std::string inputKey;
	while (running) {
		system("cls");
		printMenu();
		controller.PrintParams();
		std::cin >> inputKey;
		if (inputKey == "1") {
			system("cls");
			controller.loadGraphFromFile();
			system("pause");
		}
		else if (inputKey == "2") {
			system("cls");
			controller.ShowGraph();
			system("pause");
		}

		else if (inputKey == "3") {
			system("cls");
			controller.SetCrossover();
			system("pause");
		}
		else if (inputKey == "4") {
			system("cls");
			controller.SetMutation();
			system("pause");
		}
		else if (inputKey == "5") {
			system("cls");
			controller.SetStopTime();
			system("pause");
		}
		else if (inputKey == "6") {
			system("cls");
			controller.SetMutationMetod();
			system("pause");
		}
		else if (inputKey == "7") {
			system("cls");
			controller.SetPopulationSize();
			system("pause");
		}

		else if (inputKey == "8") {
			system("cls");
			controller.Run10000Random();
			controller.RunAlgorithm();
			system("pause");
		}

		else if (inputKey == "9") {
			system("cls");
			controller.SetTournamentSize();
			system("pause");
		}

		else if (inputKey == "10") {
			system("cls");
			controller.Run10000Random();
			system("pause");
		}


		else if (inputKey == "0") {
			return;
		}
		else {
			return;
		}
	}
}

void UserInterface::printMenu() {
	std::cout << "Menu:" << std::endl;
	std::cout << "1. Wczytaj graf" << std::endl;
	std::cout << "2. Pokaz graf" << std::endl;
	std::cout << "3. Podaj wspolcznnik krzyzowania" << std::endl;
	std::cout << "4. Podaj wspolcznnik mutacji" << std::endl;
	std::cout << "5. Podaj czas stop" << std::endl;
	std::cout << "6. Podaj metod� mutacji" << std::endl;
	std::cout << "7. Poadj rozmiar populacji" << std::endl;
	std::cout << "8. Uruchom algorytm" << std::endl;
	std::cout << "9. Podaj rozmiar turnieju" << std::endl;
	std::cout << "10. Uruchom losowe pobieranie" << std::endl;
	std::cout << "0. Wylacz" << std::endl;
}