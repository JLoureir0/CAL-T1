/*
 * Main.cpp
 *
 *  Created on: 16/04/2014
 *      Author: Daniel Moreira
 */

#include <iostream>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include "FileReader.h"
#include "Graph.h"
#include "UI.h"
#include "graphviewer.h"

int main() {
	FileReader fr = FileReader();
	UI* userInterface = new UI(fr);
	userInterface->mainMenu();
  Graph<Localidade> graph;
	graph = fr.getGraph();
	//fr.~FileReader();
	//userInterface->~UI();
	return 0;
}
