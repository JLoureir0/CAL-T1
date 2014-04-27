/*
 * Main.cpp
 *
 *  Created on: 16/04/2014
 *      Author: Daniel Moreira
 */

#include "FileReader.h"
#include "Graph.h"
#include "UI.h"

void printNodes();

Graph<Localidade> graph;

int main() {
	FileReader fr = FileReader();
	UI* userInterface = new UI(&fr);
	userInterface->mainMenu();
	graph = fr.getGraph();

	int mode = userInterface->getMenuOption();
	switch (mode) {
		case 1:
			definedRange = userInterface->getRange();
			cout << endl << endl;
			cout << "*** Graph Nodes ***" << endl;
			graph.drawGraph();
			printNodes();
			cout << endl << endl;
			graph.testRangeFunction();
			graph.attributeHealthUnits();
			break;
		case 2:
			numMaxUnidadesSaude = userInterface->getMaxHealthUnits();
			cout << endl << endl;
			cout << "*** Graph Nodes ***" << endl;
			graph.drawGraph();
			printNodes();
			cout << endl << endl;
			graph.attributeHealthUnitsStage2();
			break;
		default:
			break;
	}

	std::string dontClose;
	cin >> dontClose;

	return 0;
}

void printNodes() {
	vector<Vertex<Localidade>*> vertices = graph.getVertexSet();
	cout << "size: " << vertices.size() << endl;
	for(unsigned int i = 0; i < vertices.size(); i++) {
		cout << "Localidade: " << vertices[i]->getInfo().getNome() << " Populacao: " << vertices[i]->getInfo().getPopulacao() << endl;
	}
}


