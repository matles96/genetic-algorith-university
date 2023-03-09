#include "Controller.h"
#include "Controller.h"

Controller::Controller() : geneticAlgorithm(GeneticAlgorithm()) {}
Controller::~Controller() {}


void Controller::ShowGraph() {
	geneticAlgorithm.PrintGraph();
}

void Controller::loadGraphFromFile()
{
	std::string filename;
	std::cout << "podaj nazwe pliku: ";
	std::cin >> filename;
	geneticAlgorithm.ReadTSPFile(filename);
}

long long int Controller::read_QPC()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return((long long int)count.QuadPart);
}




void Controller::PrintParams()
{
	std::cout << std::endl << "Parametry: " << std::endl;
	std::cout << "crossover: " << geneticAlgorithm.crossover << std::endl;
	std::cout << "mutation: " << geneticAlgorithm.mutation << std::endl;
	std::cout << "turnamentSize: " << geneticAlgorithm.turnamentSize << std::endl;
	std::cout << "populationSize: " << geneticAlgorithm.populationSize << std::endl;
	std::cout << "stopTime: " << geneticAlgorithm.stopTime << std::endl;
	std::cout << "mutationMethod: " << geneticAlgorithm.mutationMethod << std::endl;
	//std::cout << "crossoverMethod: " << geneticAlgorithm.crossoverMethod << std::endl;
}

void Controller::Run10000Random()
{
	geneticAlgorithm.RunRandom();
	geneticAlgorithm.RunGreedy();
}


void Controller::SetMutation()
{
	float variable;
	std::cout << "podaj wsp?czynnik mutacji: ";
	std::cin >> variable;
	geneticAlgorithm.mutation = variable;
}

void Controller::SetStopTime()
{
	long long variable;
	std::cout << "podaj czas wykonywania: ";
	std::cin >> variable;
	geneticAlgorithm.stopTime = variable;
}

void Controller::SetMutationMetod()
{
	int variable;
	std::cout << "podaj metod? mutacji: (1.INVERT 2.TRANSPOSITION)";
	std::cin >> variable;
	if (variable == 1)
		geneticAlgorithm.mutationMethod = "INVERT";
	if (variable == 2)
		geneticAlgorithm.mutationMethod = "TRANSPOSITION";

}

void Controller::SetCrossover()
{
	float variable;
	std::cout << "podaj wspolczynnik krzy?owania: ";
	std::cin >> variable;
	geneticAlgorithm.crossover = variable;
}

void Controller::SetPopulationSize()
{
	int variable;
	std::cout << "podaj rozmiar populacji: ";
	std::cin >> variable;
	geneticAlgorithm.populationSize = variable;
}

void Controller::SetTournamentSize()
{
	int variable;
	std::cout << "podaj rozmiar turnieju: ";
	std::cin >> variable;
	geneticAlgorithm.turnamentSize = variable;
}



void Controller::RunAlgorithm()
{
	int how_many_times = 6;
	std::vector<std::vector<int>> zmienne;
	std::vector<std::vector<float>> zmienne2;
	zmienne.push_back(std::vector<int> { 100, 5 });
	zmienne2.push_back(std::vector<float> { 0.1, 0.7 });

	zmienne.push_back(std::vector<int> { 150, 5 });
	zmienne2.push_back(std::vector<float> { 0.1, 0.7 });

	zmienne.push_back(std::vector<int> { 50, 5 });
	zmienne2.push_back(std::vector<float> { 0.1, 0.7 });

	zmienne.push_back(std::vector<int> { 100, 5 });
	zmienne2.push_back(std::vector<float> { 0.1, 0.9 });

	zmienne.push_back(std::vector<int> { 100, 5 });
	zmienne2.push_back(std::vector<float> { 0.1, 0.5 });

	zmienne.push_back(std::vector<int> { 100, 5 });
	zmienne2.push_back(std::vector<float> { 0.05, 0.7 });

	zmienne.push_back(std::vector<int> { 100, 5 });
	zmienne2.push_back(std::vector<float> { 0.3, 0.7 });



	for (int x = 0; x< zmienne.size(); x++)
	{
		geneticAlgorithm.populationSize = zmienne[x][0];
		geneticAlgorithm.turnamentSize = zmienne[x][1];
		geneticAlgorithm.mutation = zmienne2[x][0];
		geneticAlgorithm.crossover = zmienne2[x][1];
		geneticAlgorithm.mutationMethod = "INVERT";
		geneticAlgorithm.crossoverMethod = "OX";
		geneticAlgorithm.initializationMethod = "RANDOM";
		geneticAlgorithm.selectionMethod = "RULLETTE";
		std::cout << std::endl << "INVERT OX RANDOM";
		for(int i = 0; i< how_many_times;i++)
			geneticAlgorithm.runAlgorithm();
		geneticAlgorithm.mutationMethod = "TRANSPOSITION";
		geneticAlgorithm.crossoverMethod = "OX";
		geneticAlgorithm.initializationMethod = "RANDOM";
		geneticAlgorithm.selectionMethod = "RULLETTE";
		std::cout << std::endl << "TRANSPOSITION OX RANDOM";
		for (int i = 0; i < how_many_times; i++)
			geneticAlgorithm.runAlgorithm();
		geneticAlgorithm.mutationMethod = "INVERT";
		geneticAlgorithm.crossoverMethod = "PMX";
		geneticAlgorithm.initializationMethod = "RANDOM";
		geneticAlgorithm.selectionMethod = "RULLETTE";
		std::cout << std::endl << "INVERT PMX RANDOM";
		for (int i = 0; i < how_many_times; i++)
			geneticAlgorithm.runAlgorithm();
		geneticAlgorithm.mutationMethod = "TRANSPOSITION";
		geneticAlgorithm.crossoverMethod = "PMX";
		geneticAlgorithm.initializationMethod = "RANDOM";
		geneticAlgorithm.selectionMethod = "RULLETTE";
		std::cout << std::endl << "TRANSPOSITION PMX RANDOM";
		for (int i = 0; i < how_many_times; i++)
			geneticAlgorithm.runAlgorithm();
		if (geneticAlgorithm.populationSize <= 100) {
			geneticAlgorithm.mutationMethod = "INVERT";
			geneticAlgorithm.crossoverMethod = "OX";
			geneticAlgorithm.initializationMethod = "GREEDY";
			geneticAlgorithm.selectionMethod = "RULLETTE";
			std::cout << std::endl << "INVERT OX GREEDY";
			for (int i = 0; i < how_many_times; i++)
				geneticAlgorithm.runAlgorithm();
			geneticAlgorithm.mutationMethod = "TRANSPOSITION";
			geneticAlgorithm.crossoverMethod = "OX";
			geneticAlgorithm.initializationMethod = "GREEDY";
			geneticAlgorithm.selectionMethod = "RULLETTE";
			std::cout << std::endl << "TRANSPOSITION OX GREEDY";
			for (int i = 0; i < how_many_times; i++)
				geneticAlgorithm.runAlgorithm();
			geneticAlgorithm.mutationMethod = "INVERT";
			geneticAlgorithm.crossoverMethod = "PMX";
			geneticAlgorithm.initializationMethod = "GREEDY";
			geneticAlgorithm.selectionMethod = "RULLETTE";
			std::cout << std::endl << "INVERT PMX GREEDY";
			for (int i = 0; i < how_many_times; i++)
				geneticAlgorithm.runAlgorithm();
			geneticAlgorithm.mutationMethod = "TRANSPOSITION";
			geneticAlgorithm.crossoverMethod = "PMX";
			geneticAlgorithm.initializationMethod = "GREEDY";
			geneticAlgorithm.selectionMethod = "RULLETTE";
			std::cout << std::endl << "TRANSPOSITION PMX GREEDY";
			for (int i = 0; i < how_many_times; i++)
				geneticAlgorithm.runAlgorithm();
		}
		//////////////////////////////////////////////////////selectionMethod = "RULLETTE";// "TOURNAMENT";//RULLETTE
		geneticAlgorithm.mutationMethod = "INVERT";
		geneticAlgorithm.crossoverMethod = "OX";
		geneticAlgorithm.initializationMethod = "RANDOM";
		geneticAlgorithm.selectionMethod = "TOURNAMENT";
		std::cout << std::endl << "INVERT OX RANDOM";
		for (int i = 0; i < how_many_times; i++)
			geneticAlgorithm.runAlgorithm();
		geneticAlgorithm.mutationMethod = "TRANSPOSITION";
		geneticAlgorithm.crossoverMethod = "OX";
		geneticAlgorithm.initializationMethod = "RANDOM";
		geneticAlgorithm.selectionMethod = "TOURNAMENT";
		std::cout << std::endl << "TRANSPOSITION OX RANDOM";
		for (int i = 0; i < how_many_times; i++)
			geneticAlgorithm.runAlgorithm();
		geneticAlgorithm.mutationMethod = "INVERT";
		geneticAlgorithm.crossoverMethod = "PMX";
		geneticAlgorithm.initializationMethod = "RANDOM";
		geneticAlgorithm.selectionMethod = "TOURNAMENT";
		std::cout << std::endl << "INVERT PMX RANDOM";
		for (int i = 0; i < how_many_times; i++)
			geneticAlgorithm.runAlgorithm();
		geneticAlgorithm.mutationMethod = "TRANSPOSITION";
		geneticAlgorithm.crossoverMethod = "PMX";
		geneticAlgorithm.initializationMethod = "RANDOM";
		geneticAlgorithm.selectionMethod = "TOURNAMENT";
		std::cout << std::endl << "TRANSPOSITION PMX RANDOM";
		for (int i = 0; i < how_many_times; i++)
			geneticAlgorithm.runAlgorithm();
		if (geneticAlgorithm.populationSize <= 100) {
			geneticAlgorithm.mutationMethod = "INVERT";
			geneticAlgorithm.crossoverMethod = "OX";
			geneticAlgorithm.initializationMethod = "GREEDY";
			geneticAlgorithm.selectionMethod = "TOURNAMENT";
			std::cout << std::endl << "INVERT OX GREEDY";
			for (int i = 0; i < how_many_times; i++)
				geneticAlgorithm.runAlgorithm();
			geneticAlgorithm.mutationMethod = "TRANSPOSITION";
			geneticAlgorithm.crossoverMethod = "OX";
			geneticAlgorithm.initializationMethod = "GREEDY";
			geneticAlgorithm.selectionMethod = "TOURNAMENT";
			std::cout << std::endl << "TRANSPOSITION OX GREEDY";
			for (int i = 0; i < how_many_times; i++)
				geneticAlgorithm.runAlgorithm();
			geneticAlgorithm.mutationMethod = "INVERT";
			geneticAlgorithm.crossoverMethod = "PMX";
			geneticAlgorithm.initializationMethod = "GREEDY";
			geneticAlgorithm.selectionMethod = "TOURNAMENT";
			std::cout << std::endl << "INVERT PMX GREEDY";
			for (int i = 0; i < how_many_times; i++)
				geneticAlgorithm.runAlgorithm();
			geneticAlgorithm.mutationMethod = "TRANSPOSITION";
			geneticAlgorithm.crossoverMethod = "PMX";
			geneticAlgorithm.initializationMethod = "GREEDY";
			std::cout << std::endl << "TRANSPOSITION PMX GREEDY";
			geneticAlgorithm.selectionMethod = "TOURNAMENT";
			for (int i = 0; i < how_many_times; i++)
				geneticAlgorithm.runAlgorithm();
		}

	}
}




void Controller::makeFile(int size, std::string filename) {
	std::fstream file;
	file.open(filename, std::ios::out);
	if (file.is_open()) {
		file << size;
		file << "\n";
		for (int y = 0; y < size; y++) {
			for (int x = 0; x < size; x++) {
				if (x == y)
					file << 0;
				else
					file << rand() % 1000;
				file << " ";
			}
			file << "\n";
		}
	}
	file.close();
}


