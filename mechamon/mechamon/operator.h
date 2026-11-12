#pragma once
#include "generic_header.h"
#include "mechamon.h"
#include "consts.h"
#include "text_output_handler.h"

const uint8_t OPERATOR_FLAG_RAN = 0b0001;

struct Operator {
public:
	Operator(string _name) {
		name = _name;
	}
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
	void addMechamonToList(Mechamon newMechamon, uint8_t mechamonLimit = MECHAMON_LIMIT) {
		if (mechamonList.size() < mechamonLimit) {
			mechamonList.push_back(newMechamon);
		}
		if (mechamonList.size() == 1) {
			curMechamonIndex = 0;
		}
	}
	void setRanFromBattle(bool ran) {
		if (ran) {
			statusFlags = statusFlags | OPERATOR_FLAG_RAN;
		}
		else {
			statusFlags = statusFlags & ~OPERATOR_FLAG_RAN;
		}
	}
	bool readRanFromBattle() {
		return (statusFlags & OPERATOR_FLAG_RAN);
	}
	void healAllMechamons() {
		for (Mechamon mechamon : mechamonList) {
			mechamon.healDamage();
		}
	}
private:
	string name;
	vector<Mechamon> mechamonList = {};
	int curMechamonIndex = -1;
	uint8_t statusFlags = 0b0000;
};