/*
 * UI.cpp
 *
 *  Created on: 16/04/2014
 *      Author: Daniel Moreira
 */

#include "UI.h"

using namespace std;

UI::UI(FileReader* fr) {
	this->fr = fr;
	this->maxHealthUnits = 0;
	this->range = 0;
	this->menuOption = 0;
}

void UI::mainMenu() {

	while(true) {
		cout << "*********** Menu ********** \n";
		cout << "1 -> Distribute health units \n";
		cout << "2 -> Minimize the medium distance for the population that has to travel to an health unit for a fixed number of health units \n";
		cout << "3 -> Exit \n";
		cout << "Option: ";

		string response;
		cin >> response;
		int option = atoi(response.c_str());

		switch (option) {
			case 1:
				distributeUnitMenu(1);
				return;
				break;
			case 2:
				distributeUnitMenu(2);
				return;
				break;
			case 3:
				cout << "... Closing ... \n";
				exit(0);
				break;
			default:
				break;
		}
		printf("\n");
	}
}

void UI::getMaxDistanceBeetweenHealthUnits() {
	while(true) {
		cout << "Type the maximum distance that a city may be within range: ";
		int maxDist;
		cin >> maxDist;
		if (cin) {  // input was an integer
			range = maxDist;
			break;
		}
	}
}

void UI::distributeUnitMenu(int mode) {
	while(true) {
		cout << "1 -> Load from a file \n";
		cout << "2 -> Go back \n";
		cout << "Option: ";
		string response;
		cin >> response;
		int option = atoi(response.c_str());

		switch (option) {
			case 1:
				getFilePath(mode);
				return;
				break;
			case 2:
				mainMenu();
				return;
			default:
				break;
		}
	}
}

void UI::getFilePath(int mode) {
	menuOption = mode;
	cout << "File name: ";
	string path;
	cin >> path;
	fr->setPath(path);

	switch (mode) {
		case 1:
			getMaxDistanceBeetweenHealthUnits();
			break;
		case 2:
			minimizeUnitsMenu();
			break;
		default:
			break;
	}

	fr->readFile();
}

void UI::minimizeUnitsMenu() {
	getMaxUnits();
}

void UI::getMaxUnits() {
	while(true) {
		cout << "Type the number of health units that the region must have: ";
		int max;
		cin >> max;
		if (cin) {  // input was an integer
			maxHealthUnits = max;
			break;
		}
	}
}

int UI::getRange() {
	return range;
}

int UI::getMaxHealthUnits() {
	return maxHealthUnits;
}

int UI::getMenuOption() {
	return menuOption;
}
