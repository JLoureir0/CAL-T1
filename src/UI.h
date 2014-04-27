/*
 * UI.h
 *
 *  Created on: 16/04/2014
 *      Author: Daniel Moreira
 */

#ifndef UI_H_
#define UI_H_

#include <iostream>
#include <cstdlib>
#include "FileReader.h"
#include "Localidade.h"
#include "Graph.h"

using namespace std;

class UI {
public:
	UI(FileReader* fr);
	void mainMenu();
	void distributeUnitMenu(int mode);
	void getFilePath(int mode);
	void minimizeUnitsMenu();
	void getMaxDistanceBeetweenHealthUnits();
	int getRange();
	int getMaxHealthUnits();
	int getMenuOption();
	void getMaxUnits();
private:
	FileReader* fr;
	int range;
	int maxHealthUnits;
	int menuOption;
};

#endif


