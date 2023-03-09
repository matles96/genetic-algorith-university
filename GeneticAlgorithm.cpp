#include "GeneticAlgorithm.h"

GeneticAlgorithm::GeneticAlgorithm()
{
	stopTime = 100;
	populationSize = 120;
	turnamentSize = 5;
	mutation = 0.15;
	crossover = 0.80;
	mutationMethod = "INVERT";
	crossoverMethod = "OX";
	initializationMethod = "RANDOM";
	selectionMethod = "RULLETTE";// "TOURNAMENT";//RULLETTE
	measurement_time = 4;
	mesurment_filename = "file_measure.txt";
	experiment = false;
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}



void GeneticAlgorithm::LogEAResults(int gen)
{
	long min = std::numeric_limits<long>::max();
	long max = 0;
	long long avg = 0;
	for (int i = 0; i < populationSize; i++) {
		if (population.at(i).second < min)
			min = population.at(i).second;
		if (population.at(i).second > max)
			max = population.at(i).second;
		avg += population.at(i).second;
	}
	avg = avg / populationSize;

	std::fstream file;
	std::string name_file = "f_"+ this->fileName +"\\results_" + this->fileName + "_" + mutationMethod + "_" + crossoverMethod + "_" + selectionMethod + "_" + initializationMethod + "_" + std::to_string(populationSize) + "_" + std::to_string(turnamentSize) + "_" + std::to_string(mutation) + "_" + std::to_string(crossover) + ".csv";
	file.open(name_file, std::ios::app);
	file << std::endl << gen << "," << max << "," << min << "," << avg;
	file.close();

	name_file = "f_" + this->fileName + "\\results_" + this->fileName + ".csv";
	file.open(name_file, std::ios::app);
	file << std::endl << mutationMethod + "_" + crossoverMethod + "_" + selectionMethod + "_" + initializationMethod + "_" + std::to_string(populationSize) + "_" + std::to_string(turnamentSize) + "_" + std::to_string(mutation) + "_" + std::to_string(crossover) << gen << "," << max << "," << min << "," << avg;
	file.close();
}


void GeneticAlgorithm::WheelRullete()
{
	roulette.clear();
	srand((unsigned)time(NULL));
	double roll;
	unsigned long long rouletteTotalDist = 0;
	for (int i = 0; i < populationSize; i++) {
		rouletteTotalDist += static_cast <unsigned long long>(population[i].second);
	}
	double chance = 0;
	for (int i = 0; i < populationSize; i++) {
		chance += (1.0 / (populationSize - 1.0)) * (1.0 - (population[i].second / rouletteTotalDist));
		roulette.push_back(chance);
	}

	for (int i = 0; i < populationSize; i++) {
		roll = (double)rand() / RAND_MAX;
		for (int j = 0; j < roulette.size(); j++) {
			if (roll < roulette[j]) {
				parentPopulation.push_back(population[j].first);
				break;
			}
		}
	}

}


void GeneticAlgorithm::runAlgorithm()
{
	//std::fstream file;
	//file.open(mesurment_filename, std::ios::out);
	//bool is_first_time = true;

	GenerateInitialPopulation();

	//ActualBestRoute = std::make_pair(std::vector<int>{}, std::numeric_limits<int>::max());
	std::vector<std::pair<std::vector<int>, int>> tournament;

	LogEAResults(0);
	for (int generation_number = 0; generation_number < stopTime; generation_number++) {
		//Elite(populationSize / 25);
		parentPopulation.clear();
		childrenPopulation.clear();

		if (selectionMethod == "TOURNAMENT") {
			for (int i = 0; i < populationSize; i++) {

				tournament.clear();
				for (int j = 0; j < turnamentSize; j++) {
					int randomInt = GetRandomInt(0, population.size());
					tournament.push_back(population.at(randomInt));
				}
				parentPopulation.push_back(Tournament(tournament));
			}
		}
		else if (selectionMethod == "RULLETTE") {
			WheelRullete();
		}

		LogEAResults(generation_number+1);
		Crossover();
		Mutation();

		population.clear();

		//population = elitePopulation;
		

		for (int i = 0; i < childrenPopulation.size(); i++) {
			population.push_back(std::make_pair(childrenPopulation.at(i), CalculateRouteCost(childrenPopulation.at(i))));
		}
		/*
		int min_cost = std::numeric_limits<int>::max();
		int min_index = 0;
		for (int i = 0; i < population.size(); i++) {
			if (population.at(i).second < min_cost) {
				min_cost = population.at(i).second;
				min_index = i;
			}
		}


		if (min_cost < ActualBestRoute.second) {
			ActualBestRoute = population.at(min_index);
		}
		*/
		
	}


	LogEAResults(stopTime);

	

}



void GeneticAlgorithm::Elite(int eliteSize)
{
	elitePopulation.clear();

	int minValue1 = std::numeric_limits<int>::max();
	int minValue2 = std::numeric_limits<int>::max();
	std::pair<std::vector<int>, int> route;
	for (int i = 0; i < population.size(); i++) {
		if (population.at(i).second < minValue1) {
			minValue1 = population.at(i).second;
			route = population.at(i);
		}
	}

	for (int k = 0; k < eliteSize - 1; k++) {
		minValue2 = std::numeric_limits<int>::max();
		for (int i = 0; i < population.size(); i++) {
			if (population.at(i).second < minValue2 && population.at(i).second > minValue1) {
				minValue2 = population.at(i).second;
				route = population.at(i);
			}
		}
		minValue1 = minValue2;
		elitePopulation.push_back(route);
	}

}

long double GeneticAlgorithm::CalculateRouteCost(std::vector<int> Route)
{
	long double cost = 0;
	for (int i = 0; i < size - 1; i++) {
		cost += graph(Route.at(i), Route.at(i + 1));
	}
	cost += graph(Route.at(size - 1), Route.at(0));
	return cost;
}

int GeneticAlgorithm::GetRandomInt(int min, int max)
{
	return (std::rand() % (max - min)) + min;
}

int GeneticAlgorithm::GetRandomFloat()
{
	return (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
}

std::vector<int> GeneticAlgorithm::Tournament(std::vector<std::pair<std::vector<int>, int>> tournam)
{
	int min = std::numeric_limits<int>::max();
	std::vector<int> min_vec;
	for (int i = 0; i < tournam.size(); i++) {
		if (tournam.at(i).second < min) {
			min = tournam.at(i).second;
			min_vec = tournam.at(i).first;
		}
	}
	return min_vec;
}



void GeneticAlgorithm::Crossover()
{
	if(crossoverMethod == "PMX"){
		int firstParent, secondParent;
		while (parentPopulation.size() > 0) {

			firstParent = GetRandomInt(0, parentPopulation.size());
			do {
				secondParent = GetRandomInt(0, parentPopulation.size());
			} while (firstParent == secondParent);
			if (GetRandomFloat() < crossover) {
				DoCrossover(parentPopulation.at(firstParent), parentPopulation.at(secondParent));
				//childrenPopulation.push_back(parentPopulation.at(firstParent));
				//childrenPopulation.push_back(parentPopulation.at(secondParent));
			}
			else {
				childrenPopulation.push_back(parentPopulation.at(firstParent));
				childrenPopulation.push_back(parentPopulation.at(secondParent));
			}
			parentPopulation.erase(parentPopulation.begin() + firstParent);
			if (secondParent > firstParent)
				parentPopulation.erase(parentPopulation.begin() + secondParent - 1);
			else
				parentPopulation.erase(parentPopulation.begin() + secondParent);
		}
	}
	if (crossoverMethod == "OX") {
		int firstParent, secondParent;
		while (parentPopulation.size() > 0) {

			firstParent = GetRandomInt(0, parentPopulation.size());
			do {
				secondParent = GetRandomInt(0, parentPopulation.size());
			} while (firstParent == secondParent);
			if (GetRandomFloat() < crossover) {
				DoCrossoverOX(parentPopulation.at(firstParent), parentPopulation.at(secondParent));
				//childrenPopulation.push_back(parentPopulation.at(firstParent));
				//childrenPopulation.push_back(parentPopulation.at(secondParent));
			}
			else {
				childrenPopulation.push_back(parentPopulation.at(firstParent));
				childrenPopulation.push_back(parentPopulation.at(secondParent));
			}
			parentPopulation.erase(parentPopulation.begin() + firstParent);
			if (secondParent > firstParent)
				parentPopulation.erase(parentPopulation.begin() + secondParent - 1);
			else
				parentPopulation.erase(parentPopulation.begin() + secondParent);
		}
	}
}


void GeneticAlgorithm::DoCrossover(std::vector<int> vec1, std::vector<int> vec2)
{
	int cuttingStartIndex, cuttingEndIndex;
	cuttingStartIndex = GetRandomInt(0, vec1.size());
	do {
		cuttingEndIndex = GetRandomInt(0, vec1.size());
	} while (cuttingEndIndex == cuttingStartIndex);



	if (cuttingStartIndex > cuttingEndIndex) {
		int tmp = cuttingStartIndex;
		cuttingStartIndex = cuttingEndIndex;
		cuttingEndIndex = tmp;
	}
	std::vector<int> cutVector1 = { vec1.begin() + cuttingStartIndex, vec1.begin() + cuttingEndIndex };
	std::vector<int> cutVector2 = { vec2.begin() + cuttingStartIndex, vec2.begin() + cuttingEndIndex };

	std::vector<int> child1 = vec1;
	std::vector<int> child2 = vec2;

	for (int i = 0; i < cutVector1.size(); i++) {
		child1.at(i + cuttingStartIndex) = cutVector2.at(i);
		child2.at(i + cuttingStartIndex) = cutVector1.at(i);
	}

	bool isBad = false;
	for (int i = 0; i < child1.size(); i++) {
		if ((i < cuttingStartIndex) || (i >= cuttingEndIndex)) {
			do {
				isBad = false;
				for (int j = 0; j < cutVector2.size(); j++) {
					if (child1.at(i) == cutVector2.at(j)) {
						isBad = true;
						child1.at(i) = cutVector1.at(j);
						break;
					}
				}
			} while (isBad);
		}
	}

	childrenPopulation.push_back(child1);

	for (int i = 0; i < child2.size(); i++) {
		if ((i < cuttingStartIndex) || (i >= cuttingEndIndex)) {
			do {
				isBad = false;
				for (int j = 0; j < cutVector1.size(); j++) {
					if (child2.at(i) == cutVector1.at(j)) {
						isBad = true;
						child2.at(i) = cutVector2.at(j);
						break;
					}
				}
			} while (isBad);
		}
	}

	childrenPopulation.push_back(child2);


}

void GeneticAlgorithm::DoCrossoverOX(std::vector<int> vec1, std::vector<int> vec2)
{
	int cuttingStartIndex, cuttingEndIndex;
	cuttingStartIndex = GetRandomInt(0, vec1.size());
	do {
		cuttingEndIndex = GetRandomInt(0, vec1.size());
	} while (cuttingEndIndex == cuttingStartIndex);



	if (cuttingStartIndex > cuttingEndIndex) {
		int tmp = cuttingStartIndex;
		cuttingStartIndex = cuttingEndIndex;
		cuttingEndIndex = tmp;
	}
	std::vector<int> cutVector1 = { vec1.begin() + cuttingStartIndex, vec1.begin() + cuttingEndIndex };
	std::vector<int> cutVector2 = { vec2.begin() + cuttingStartIndex, vec2.begin() + cuttingEndIndex };

	std::vector<int> child1 = vec1;
	std::vector<int> child2 = vec2;

	/*
	for (int i = 0; i < cutVector1.size(); i++) {
		child1.at(i + cuttingStartIndex) = cutVector2.at(i);
		child2.at(i + cuttingStartIndex) = cutVector1.at(i);
	}
	*/


	for (int i = 0; i < child1.size(); i++) {
		if ((i < cuttingStartIndex) || (i >= cuttingEndIndex)) {
			for (int j = 0; j < child2.size(); j++) {
				bool jest = false;
				for (int k = 0; k < cutVector1.size(); k++) {
					if (vec2.at(j) == cutVector1.at(k)) {
						jest=true;
					}
				}
				for (int k = 0; k < i; k++) {
					if (vec2.at(j) == child1.at(k)) {
						jest = true;
					}
				}
				if (!jest) {
					child1.at(i) = vec2.at(j);
					break;
				}
			}
		}
	}

	for (int i = 0; i < child2.size(); i++) {
		if ((i < cuttingStartIndex) || (i >= cuttingEndIndex)) {
			for (int j = 0; j < child1.size(); j++) {
				bool jest = false;
				for (int k = 0; k < cutVector2.size(); k++) {
					if (vec1.at(j) == cutVector2.at(k)) {
						jest = true;
					}
				}
				for (int k = 0; k < i; k++) {
					if (vec1.at(j) == child2.at(k)) {
						jest = true;
					}
				}
				if (!jest){
					child2.at(i) = vec1.at(j);
					break;
				}
			}
		}
	}


	childrenPopulation.push_back(child1);
	childrenPopulation.push_back(child2);


}



void GeneticAlgorithm::GenerateInitialPopulation()
{
	if (initializationMethod == "RANDOM") {
		population.clear();
		std::vector<int> startRoute;
		std::vector<int> tmpRoute;
		for (int i = 0; i < size; i++) {
			startRoute.push_back(i);
		}
		for (int i = 0; i < populationSize; i++) {
			tmpRoute = startRoute;
			std::random_shuffle(tmpRoute.begin(), tmpRoute.end());
			population.push_back(std::make_pair(tmpRoute, CalculateRouteCost(tmpRoute)));
		}
	}
	else if ((initializationMethod) == "GREEDY" && (populationSize <= size)) {
		population.clear();
		std::vector<int> startRoute;
		std::vector<int> tmpRoute;
		for (int i = 0; i < size; i++) {
			startRoute.push_back(i);
		}


		for (int startNode = 0; startNode < populationSize; startNode++) {
			std::vector<int> actualRoute;
			actualRoute.push_back(startNode);
			long actualRouteLength = 0;
			std::vector<bool> visited;
			visited.resize(size, false);
			int actual_node = startNode;

			for (int iteration = 0; iteration < size; iteration++) {
				long minCost = std::numeric_limits<int>::max();
				int nextNode = startNode;
				for (int node = 0; node < size; node++) {
					if (node == actual_node)
						continue;
					if (node == startNode)
						continue;
					if (visited.at(node))
						continue;

					if (graph(actual_node, node) < minCost) {
						minCost = graph(actual_node, node);
						nextNode = node;
						actual_node = node;
					}
				}
				if (iteration == size - 1) {
					minCost = graph(actual_node, startNode);
					nextNode = startNode;
					actual_node = startNode;
					continue;
				}
				actualRouteLength += minCost;
				actualRoute.push_back(nextNode);
				visited.at(nextNode) = true;
			}
			population.push_back(std::make_pair(actualRoute, CalculateRouteCost(actualRoute)));
		}
	}
}


void GeneticAlgorithm::Mutation()
{
	int random2, random1, tmp, tmp2;
	for (int i = 0; i < childrenPopulation.size(); i++) {
		if (mutation > GetRandomFloat()) {
			if (mutationMethod == "INVERT") {
				random1 = GetRandomInt(0, childrenPopulation.at(i).size());
				do {
					random2 = GetRandomInt(0, childrenPopulation.at(i).size());
				} while (random1 == random2);
				if (random1 > random2) {
					tmp2 = random1;
					random1 = random2;
					random2 = tmp2;
				}

				std::vector<int> cutVector1 = { childrenPopulation.at(i).begin() + random1, childrenPopulation.at(i).begin() + random2 };
				for (int a = 0, b = random2 - 1; a < cutVector1.size(); a++, b--) {
					childrenPopulation.at(i).at(b) = cutVector1.at(a);
				}
			}
			else if (mutationMethod == "TRANSPOSITION") {
				random1 = GetRandomInt(0, childrenPopulation.at(i).size());
				do {
					random2 = GetRandomInt(0, childrenPopulation.at(i).size());
				} while (random1 == random2);
				tmp = childrenPopulation.at(i).at(random1);
				childrenPopulation.at(i).at(random1) = childrenPopulation.at(i).at(random2);
				childrenPopulation.at(i).at(random2) = tmp;
			}
		}
	}
}







void GeneticAlgorithm::RunRandom() {
	std::vector<int> startRoute;
	std::vector<int> tmpRoute;
	unsigned  long int bestResult = std::numeric_limits<unsigned long int>::max();
	unsigned  long int worstResult = 0;
	long double  avgResult = 0;
	unsigned  long int routeLeng;
	for (int i = 0; i < size; i++) {
		startRoute.push_back(i);
	}
	for (int i = 0; i < 10000; i++) {
		tmpRoute = startRoute;
		std::random_shuffle(tmpRoute.begin(), tmpRoute.end());
		routeLeng = CalculateRouteCost(tmpRoute);
		avgResult += routeLeng;
		if (routeLeng < bestResult) {
			bestResult = routeLeng;
		}
		if (routeLeng > worstResult) {
			worstResult = routeLeng;
		}
	}
	avgResult = avgResult / 10000;

	std::fstream file;
	file.open("results_" + this->fileName + "_" + "random_search.csv", std::ios::app);
	file << std::endl << this->fileName << "," << avgResult << "," << worstResult << "," << bestResult;
	file.close();
}

void GeneticAlgorithm::RunGreedy() {
	for (int startNode = 0; startNode < size; startNode++) {
		std::vector<int> actualRoute;
		long actualRouteLength = 0;
		std::vector<bool> visited;
		visited.resize(size, false);
		int actual_node = startNode;

		for (int iteration = 0; iteration < size; iteration++) {
			long minCost = std::numeric_limits<int>::max();
			int nextNode = startNode;
			for (int node = 0; node < size; node++) {
				if (node == actual_node)
					continue;
				if (node == startNode)
					continue;
				if (visited.at(node))
					continue;

				if (graph(actual_node, node) < minCost) {
					minCost = graph(actual_node, node);
					nextNode = node;
					actual_node = node;
				}
			}
			if (iteration == size - 1) {
				minCost = graph(actual_node, startNode);
				nextNode = startNode;
				actual_node = startNode;
			}
			actualRouteLength += minCost;
			actualRoute.push_back(nextNode);
			visited.at(nextNode) = true;
		}

		std::fstream file;
		file.open("results_" + this->fileName + "_" + "greedy_search.csv", std::ios::app);
		file << std::endl << this->fileName << "," << startNode << "," << actualRouteLength;
		file.close();
	}
}

