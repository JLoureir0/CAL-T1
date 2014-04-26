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
		cout << "1 -> Distruibuir unidades de saude \n";
		cout << "2 -> Minimizar a distancia media para deslocacao a uma unidade de saude sabendo o numero de unidades de saude \n";
		cout << "3 -> Exit \n";
		cout << "Insira a opcao que pretende: ";

		string response;
		cin >> response;
		int option = atoi(response.c_str());

		switch (option) {
			case 1:
				distributeUnitMenu();
				return;
				break;
			case 2:
				minimizeUnitsMenu();
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
		cout << "Insira a distancia / tempo maximo que uma localidade pode distar de uma Unidade de saude \n";
		int maxDist;
		cin >> maxDist;
		if (cin) {  // input was an integer
			range = maxDist;
			break;
		}
	}
}

void UI::distributeUnitMenu() {
	while(true) {
		cout << "1 -> Carregar de um ficheiro \n";
		cout << "2 -> Retroceder \n";
		cout << "Insira a opcao que pretende: ";
		string response;
		cin >> response;
		int option = atoi(response.c_str());

		switch (option) {
			case 1:
				getFilePath(1);
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
	cout << "Insira o nome ou caminho do ficheiro a ler \n";
	string path;
	cin >> path;
	fr->setPath(path);

	switch (mode) {
		case 1:
			getMaxDistanceBeetweenHealthUnits();
			break;
		case 2:
			getMaxUnits();
			break;
		default:
			break;
	}

	fr->readFile();
}

void UI::minimizeUnitsMenu() {
	getFilePath(2);
}

void UI::getMaxUnits() {
	while(true) {
		cout << "Insira o numero maximo de unidades de saude na regiao \n";
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
