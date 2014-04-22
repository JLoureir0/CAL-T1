/*
 * FileReader.cpp
 *
 *  Created on: 16/04/2014
 *      Author: Daniel Moreira
 */

#include "FileReader.h"
#include <stdlib.h>

using namespace std;

FileReader::FileReader() {
	this->path = "";
	this->fileDividor = "Connections";
	this->graph = Graph<Localidade>();
}

FileReader::FileReader(string path) {
	this->path = path;
	this->fileDividor = "Connections";
	this->graph = Graph<Localidade>();
}

void FileReader::setPath(string path) {
	this->path = path;
}

Graph<Localidade> FileReader::getGraph() {
	return graph;
}

//FileReader::~FileReader() {
//	delete(&path);
//	delete(&fileDividor);
//	delete(&graph);
//	delete(&localidades);
//}

void FileReader::createEdge(string localidade1, string localidade2, double weight) {
	Localidade source;
	Localidade destiny;
	for(unsigned int i=0; i < localidades.size(); i++) {
		if(localidades[i].getNome() == localidade1)
			source = localidades[i];
		else if(localidades[i].getNome() == localidade2) {
			destiny = localidades[i];
			break;
		}
	}
	cout << "before addEdge" << endl;
	this->graph.addEdge(source,destiny,weight);
	cout << "after addEdge" << endl;
}

void FileReader::readFile() {
	cout << "ReadFile" << endl;
	string line;
	string nomeRegiao;
	ifstream file (path.c_str());
	bool readingConnections = false;

	if (file.is_open()) {
		while ( getline(file,line) ) {
			cout << "No while" << endl;
			if(readingConnections) {
				cout << "no if" << endl;
				string localidade2;
				string dist;
				string localidade1 = ""+line;
				getline(file,localidade2);
				getline(file,dist);
				cout << "going to create edge" << endl;
				createEdge(localidade1,localidade2,52.2);
				cout << "end of if" << endl;
			}
			else if(line == this->fileDividor) {
				readingConnections = true;
				cout << "Going to read Connections" << endl;
			}
			else if(!readingConnections) {
				cout << "no else" << endl;
				string population;
				string name = ""+line;
				getline(file,population);
				cout << "Localidade: " << name << " " << population << endl;
				Localidade l = Localidade(name,atof(population.c_str()));
				this->graph.addVertex(l);
				this->localidades.push_back(l);
				cout << "end of else" << endl;
			}
		}
		file.close();
	}
	else {
		cout << "Unable to open file \n";
		exit(1);
	}
}



