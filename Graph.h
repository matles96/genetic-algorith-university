#pragma once
#include<fstream>
#include<iostream>
#include<string>
#include"Array2d.h"
#include <math.h>
#include <vector>

class Graph
{
protected:
	int size;
	Array2d<int> graph;
	std::string fileName;
public:
	Graph();
	~Graph();
	void PrintGraph();
	void ReadTSPFile(std::string fileName);
};
