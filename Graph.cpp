#include "Graph.h"
#include <limits>
//#include <string>

Graph::Graph() : graph(Array2d<int>()) {
	size = 0;
}
Graph::~Graph() {
}


void Graph::ReadTSPFile(std::string fileName) {
	std::fstream file;
	std::string input = "";
	int node = 0;
	
	file.open(fileName, std::ios::in);
	if (file.is_open()) {
		while (input != "DIMENSION:")
			file >> input;
		file >> input;
		size = std::stoi(input);
		graph.resize(size);
		float* x_coord = new float[size];
		float* y_coord = new float[size];
		while (input != "NODE_COORD_SECTION") {
			file >> input;
		}
		for (int i = 0; i < size; i++) {
			file >> input;
			node = std::stoi(input) - 1;
			file >> input;
			x_coord[node] = std::stof(input);
			file >> input;
			y_coord[node] = std::stof(input);
		}

		float maxx = 0;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (i == j)
					graph(i, j) = 0;
				else {
					float p1 = pow((x_coord[i] - x_coord[j]), 2);
					float p2 = pow((y_coord[i] - y_coord[j]), 2);
					float sq = sqrt(p1 + p2);
					graph(i, j) = static_cast<int>(sq);

				}
				
			}
		}
		delete[] x_coord;
		delete[] y_coord;
		
	}
	file.close();
	this->fileName = fileName;
}
void Graph::PrintGraph() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			std::cout << graph(i, j) << " ";
		}
		std::cout << std::endl;
	}
}




