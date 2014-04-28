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
#include "City.h"

class FileReader {
public:
	FileReader();
	void readFile();
	void setPath(std::string path);
	Graph<City> getGraph();
	void addCitys();
	void createEdge(string city1, string city2, string dist);
private:
	std::string path;
	std::string fileDividor;
	Graph<City> graph;
	std::vector<City> cities;
};

#endif /* FILEREADER_H_ */
