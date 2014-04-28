/*
 * FileReader.cpp
 *
 *  Created on: 16/04/2014
 *      Author: Daniel Moreira
 */

#include "FileReader.h"
#include "Constants.h"

using namespace std;

FileReader::FileReader() {
  path = "";
  fileDividor = "Connections";
  graph = Graph<City>();
}

void FileReader::setPath(string path) {
	this->path = path;
}

Graph<City> FileReader::getGraph() {
	return graph;
}

void FileReader::createEdge(string city1, string city2, string weight) {
	City source;
	City destiny;
	for (unsigned int i = 0; i < cities.size(); i++) {
		if (cities[i].getName() == city1)
			source = cities[i];
		else if (cities[i].getName() == city2) {
			destiny = cities[i];
		}
	}
	this->graph.addEdge(source, destiny, atof(weight.c_str()));
}

void FileReader::readFile() {
	cout << "Reading File ..." << endl;
	string line;
	string regionName;
	ifstream file(path.c_str());
	bool readingConnections = false;

	if (file.is_open()) {
		while (getline(file, line)) {
			if (readingConnections) {
				string city2;
				string dist;
				string city1 = "" + line;
				getline(file, city2);
				getline(file, dist);
				createEdge(city1, city2, dist);
			} else if (line == this->fileDividor) {
				readingConnections = true;
			} else if (!readingConnections) {
				string population;
				string name = "" + line;
				getline(file, population);
				City l = City(name, atol(population.c_str()));

				this->graph.addVertex(l);
				this->cities.push_back(l);
			}
		}
		file.close();
	} else {
		cout << "Unable to open file \n";
		exit(1);
	}
}
