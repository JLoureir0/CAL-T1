/*
 * Main.cpp
 *
 *  Created on: 16/04/2014
 *      Author: Daniel Moreira
 */

#include <iostream>
#include "FileReader.h"
#include "Graph.h"
#include "UI.h"

Graph<Localidade> graph;

int main() {
	FileReader fr = FileReader();
	UI* userInterface = new UI(fr);
	userInterface->mainMenu();
	graph = fr.getGraph();
	//fr.~FileReader();
	//userInterface->~UI();
	return 0;
}


