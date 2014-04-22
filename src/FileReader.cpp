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
  graph = Graph<Localidade>();
}

void FileReader::setPath(string path) {
	this->path = path;
}

Graph<Localidade> FileReader::getGraph() {
	return graph;
}

FileReader::~FileReader() {
	delete(&path);
	delete(&fileDividor);
	delete(&graph);
	delete(&localidades);
}

void FileReader::createEdge(string localidade1, string localidade2, string weight) {
	Localidade source;
	Localidade destiny;
	for (unsigned int i = 0; i < localidades.size(); i++) {
		if (localidades[i].getNome() == localidade1)
			source = localidades[i];
		else if (localidades[i].getNome() == localidade2) {
			destiny = localidades[i];
		}
	}
	cout << "before addEdge" << endl;
	this->graph.addEdge(source, destiny, atof(weight.c_str()));
	cout << "after addEdge" << endl;
}

void FileReader::readFile() {
	cout << "ReadFile" << endl;
	string line;
	string nomeRegiao;
	ifstream file(path.c_str());
	bool readingConnections = false;

	if (file.is_open()) {
		while (getline(file, line)) {
			cout << "No while" << endl;
			if (readingConnections) {
				cout << "no if" << endl;
				string localidade2;
				string dist;
				string localidade1 = "" + line;
				getline(file, localidade2);
				getline(file, dist);
				cout << "going to create edge" << endl;
				createEdge(localidade1, localidade2, dist);
				cout << "end of if" << endl;
			} else if (line == this->fileDividor) {
				readingConnections = true;
				cout << "Going to read Connections" << endl;
			} else if (!readingConnections) {
				cout << "no else" << endl;
				string population;
				string name = "" + line;
				getline(file, population);
				cout << "Localidade: " << name << " " << population << endl;
				Localidade l = Localidade(name, atol(population.c_str()));

				this->graph.addVertex(l);
				this->localidades.push_back(l);
				cout << "end of else" << endl;
			}
		}
		file.close();
		cout << "TAMANHO FODASSE: " << graph.getVertexSet().size() << endl;
	} else {
		cout << "Unable to open file \n";
		exit(1);
	}
}
