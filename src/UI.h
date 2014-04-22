/*
 * UI.h
 *
 *  Created on: 16/04/2014
 *      Author: Daniel Moreira
 */

#ifndef UI_H_
#define UI_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "FileReader.h"
#include "Localidade.h"
#include "Graph.h"

using namespace std;

class UI {
public:
	UI(FileReader* fr);
//	virtual ~UI();
	void mainMenu();
	void distributeUnitMenu();
	void getFilePath();
	void minimizeUnitsMenu();
private:
	FileReader* fr;
};

#endif


