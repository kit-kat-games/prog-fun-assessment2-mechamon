#pragma once
#include "generic_header.h"
#include "mechamon.h"

struct Operator {
public:
	
	void setName(string newName) {
		name = newName;
	}
	string readName() {
		return name;
	}
	void addMechamonToList(Mechamon newMechamon, uint8_t MECHAMON_LIMIT) {
		if (mechamonList.size() < MECHAMON_LIMIT) {
			mechamonList.push_back(newMechamon);
		}
		if (mechamonList.size() == 1) {
			currentMechamonPtr = &(mechamonList[0]);
		}
	}
	Operator(string _name) {
		name = _name;
	}
	Mechamon* currentMechamonPtr = nullptr;
	vector<Mechamon>* mechamonListPtr = &mechamonList;
private:
	string name;
	vector<Mechamon> mechamonList = {};
};