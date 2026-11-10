#pragma once
#include "generic_header.h"
#include "misc_funcs.h"
#include "text_output_handler.h"

struct MechamonConstructor {
public:
	string type;
	string name;
	MechamonConstructor(string _type, string _name = "") {
		type = _type;
		name = _name;
	}
};

struct Mechamon {
public:
	void setName(string newName) {
		name = newName;
	}
	string readName() {
		return name;
	}
	string readType() {
		return type;
	}
	Mechamon(MechamonConstructor constructor) {
		name = constructor.name;
		type = constructor.type;
	}
private:
	string name;
	string type;
};

vector<string> _mechamonTypesList = { "mech1", "mech2", "mech3", "mech4", "mech5", "mech6", "mech7", "mech8", "mech9", "mech10", "mech11", "mech12" };

MechamonConstructor createMechamonConstructor(string mechamonType, string instanceName = "") {
	if (!isWithin(mechamonType, _mechamonTypesList)) {
		return MechamonConstructor("NOTVALIDTYPE");
	}
	return MechamonConstructor(mechamonType, instanceName);
}

vector<string> getPossibleMechamonTypes() {
	return _mechamonTypesList;
}

void displayMechamonInfo(string mechamonType) {
	int HP = 100;
	print("Type: " + mechamonType);
	print("HP: " + to_string(HP));
}