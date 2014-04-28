/*
 * City.h
 *
 *  Created on: Apr 16, 2014
 *      Author: daniel
 */

#ifndef CITY_H_
#define CITY_H_

#include <string>
#include <vector>

class City {
public:
	City();
	City(std::string name, unsigned long population);
	City(std::string name, unsigned long population, bool healthUnit);
	std::string getName() const;
	void setName(const std::string& name);
	unsigned long getPopulation() const;
	void setPopulation(unsigned long population);
	bool getHealthUnit() const;
	void setHealthUnit(bool healthUnit);
	bool operator ==(const City &l) const;
private:
	std::string name;
	unsigned long population;
	bool healthUnit;
};

#endif /* CITY_H_ */
