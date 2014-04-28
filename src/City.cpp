/*
 * City.cpp
 *
 *  Created on: Apr 16, 2014
 *      Author: daniel
 */

#include "City.h"

City::City() {
	this->name = "";
	this->population = 0;
	this->healthUnit = false;
}

City::City(std::string name, unsigned long population) {
	this->name = name;
	this->population = population;
	this->healthUnit = false;
}

City::City(std::string name, unsigned long population, bool healthUnit) {
	this->name = name;
	this->population = population;
	this->healthUnit = healthUnit;
}

std::string City::getName() const {
	return name;
}

void City::setName(const std::string& name) {
	this->name = name;
}

unsigned long City::getPopulation() const {
	return population;
}

void City::setPopulation(unsigned long population) {
	this->population = population;
}

bool City::getHealthUnit() const {
	return healthUnit;
}

void City::setHealthUnit(bool healthUnit) {
	this->healthUnit = healthUnit;
}

bool City::operator ==(const City &l) const {
	return (this->name == l.name && this->population == l.population && this->healthUnit == l.healthUnit);
}
