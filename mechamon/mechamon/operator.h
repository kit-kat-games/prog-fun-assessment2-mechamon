#pragma once
#include <string>
#include <vector>
#include <stdint.h>
#include "mechamon_classes.h"

const int MECHAMON_LIMIT = 3;
const uint8_t OPERATOR_FLAG_RAN = 0b0001;

class Operator {
public:
	// Constructor Options
	Operator() {}
	Operator(std::string _name) {
		name = _name;
	}

	// Set/Read/Get Methods
	void setName(std::string newName) {
		name = newName;
	}
	std::string readName() {
		return name;
	}
	Mechamon* getCurrentMechamonPtr() {
		return &mechamonList[curMechamonIndex];
	}
	std::vector<Mechamon>* getMechamonListPtr() {
		return &mechamonList;
	}
	bool readRanFromBattle() {
		return (statusFlags & OPERATOR_FLAG_RAN);
	}
	void setRanFromBattle(bool ran) {
		if (ran) {
			statusFlags = (statusFlags | OPERATOR_FLAG_RAN);
		}
		else {
			statusFlags = (statusFlags & ~OPERATOR_FLAG_RAN);
		}
	}
	
	// Logic Methods
	void addMechamonToList(Mechamon newMechamon, int mechamonLimit = MECHAMON_LIMIT) {
		if (mechamonList.size() < mechamonLimit) {
			mechamonList.push_back(newMechamon);
		}
		if (mechamonList.size() == 1) {
			curMechamonIndex = 0;
		}
	}
	void healAllMechamons() {
		for (Mechamon mechamon : mechamonList) {
			mechamon.healDamage();
		}
	}
private:
	// Variable Methods
	std::string name;
	std::vector<Mechamon> mechamonList = {};
	int curMechamonIndex = -1;
	uint8_t statusFlags = 0b0000;
};