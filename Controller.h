#pragma once
#pragma once
#include "GeneticAlgorithm.h"
#include <string>
#include <cstdlib>
#include<fstream>
#include <windows.h>
#include <iostream>
#include <iomanip>
class Controller
{
public:
	Controller();
	~Controller();
	void loadGraphFromFile();
	void ShowGraph();
	void PrintParams();
	void Run10000Random();
	void SetMutationMetod();
	void SetMutation();
	void SetCrossover();
	void SetPopulationSize();
	void SetTournamentSize();
	void SetStopTime();
	void RunAlgorithm();
private:
	long long int read_QPC();
	GeneticAlgorithm geneticAlgorithm;
	void makeFile(int size, std::string filename);
};

