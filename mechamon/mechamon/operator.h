#pragma once
#include "generic_header.h"
#include "mechamon.h"
#include "consts.h"
#include "text_output_handler.h"

struct Operator {
public:
	// Constructor
	Operator(string _name) {
		name = _name;
	}
	// Sets, Reads
	void setName(string newName) {
		name = newName;
	}
	string readName() {
		return name;
	}
	Mechamon* getCurrentMechamonPtr() {
		return currentMechamonPtr;
	}
	// Methods
	void addMechamonToList(Mechamon newMechamon, uint8_t mechamonLimit = MECHAMON_LIMIT) {
		if (mechamonList.size() < mechamonLimit) {
			mechamonList.push_back(newMechamon);
		}
		if (mechamonList.size() == 1) {
			currentMechamonPtr = &(mechamonList[0]);
		}
	}
private:
	string name;
	vector<Mechamon> mechamonList = {};
	Mechamon* currentMechamonPtr = nullptr;
};