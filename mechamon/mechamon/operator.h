#pragma once
#include "generic_header.h"
#include "mechamon.h"
#include "text_output_handler.h"
#include "globals.h"

const uint8_t MECHAMON_LIMIT = 3;
const uint8_t OPERATOR_FLAG_RAN = 0b0001;

class Operator {
public:
	// Constructor Options
	Operator() {}
	Operator(string _name) {
		name = _name;
	}

	// Set/Read/Get Methods
	void setName(string newName) {
		name = newName;
	}
	string readName() {
		return name;
	}
	Mechamon* getCurrentMechamonPtr() {
		return &mechamonList[curMechamonIndex];
	}
	vector<Mechamon>* getMechamonListPtr() {
		return &mechamonList;
	}
	bool readRanFromBattle() {
		return (statusFlags & OPERATOR_FLAG_RAN);
	}
	void setRanFromBattle(bool ran) {
		if (ran) {
			statusFlags = statusFlags | OPERATOR_FLAG_RAN;
		}
		else {
			statusFlags = statusFlags & ~OPERATOR_FLAG_RAN;
		}
	}
	
	// Logic Methods
	void addMechamonToList(Mechamon newMechamon, uint8_t mechamonLimit = MECHAMON_LIMIT) {
		if (mechamonList.size() < mechamonLimit) {
			mechamonList.push_back(newMechamon);
		}
		if (mechamonList.size() == 1) {
			curMechamonIndex = 0;
		}
	}
	void healAllMechamons() {
		// aaahhh
		/*for (Mechamon mechamon : mechamonList) {
			mechamon.healDamage();
		}*/
	}
private:
	// Variable Methods
	string name;
	vector<Mechamon> mechamonList = {};
	int curMechamonIndex = -1;
	uint8_t statusFlags = 0b0000;
};