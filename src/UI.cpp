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
}

UI::~UI() {
	delete(&fr);
}

void UI::mainMenu() {

	while(true) {
		cout << "*********** Menu ********** \n";
		cout << "1 -> Distruibuir unidades de saude \n";
		cout << "2 -> Minimizar a distancia media para desloca��o a uma unidade de sa�de sabendo o numero de unidades de saude \n";
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
				getFilePath();
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

void UI::getFilePath() {
	cout << "Insira o nome ou caminho do ficheiro a ler \n";
	string path;
	cin >> path;
	fr->setPath(path);
	fr->readFile();
}

void UI::minimizeUnitsMenu() {
	return;
}
