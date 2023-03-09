#pragma once
#include "graph.h"
#include <algorithm>
#include <cstdlib> 
#include <ctime>
#include <math.h>
#include <chrono>
#include <utility>
#include<fstream>

class GeneticAlgorithm : public Graph {
private:
	std::vector<std::pair<std::vector<int>, int>> population;
	std::vector<std::vector<int>> parentPopulation;
	std::vector<std::vector<int>> childrenPopulation;
	std::vector<std::pair<std::vector<int>, int>> elitePopulation;

	void GenerateInitialPopulation();
	long double CalculateRouteCost(std::vector<int> Route);

	int GetRandomInt(int min, int max);
	int GetRandomFloat();

	std::vector<int> Tournament(std::vector<std::pair<std::vector<int>, int>> tournam);
	void Mutation();
	void Crossover();
	void WheelRullete();
	void DoCrossover(std::vector<int> vec1, std::vector<int> vec2);
	void DoCrossoverOX(std::vector<int> vec1, std::vector<int> vec2);

	void LogEAResults(int gen);
	void Elite(int eliteSize);

	std::vector<double> roulette;

public:
	GeneticAlgorithm();
	~GeneticAlgorithm();
	void runAlgorithm();
	int stopTime;
	long long routeFindTime;
	std::pair<std::vector<int>, int> ActualBestRoute;
	int populationSize;
	int turnamentSize;
	float mutation;
	float crossover;
	std::string mutationMethod;
	std::string crossoverMethod;
	std::string initializationMethod;
	std::string selectionMethod;
	void RunRandom();
	void RunGreedy();

	long long measurement_time;
	std::string mesurment_filename;
	bool experiment;

};


