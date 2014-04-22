/*
 * FileReader.h
 *
 *  Created on: 16/04/2014
 *      Author: Daniel Moreira
 */

#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <iostream>
#include <fstream>
#include "graphviewer.h"
#include "Graph.h"
#include "Localidade.h"

class FileReader {
public:
	FileReader();
	void readFile();
	void setPath(std::string path);
	Graph<Localidade> getGraph();
	void addLocalidades();
	void createEdge(string localidade1, string localidade2, string dist);
private:
	std::string path;
	std::string fileDividor;
	Graph<Localidade> graph;
	std::vector<Localidade> localidades;
};

#endif /* FILEREADER_H_ */
