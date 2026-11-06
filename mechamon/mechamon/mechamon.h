#pragma once
#include "generic_header.h"

struct MechamonConstructor {
public:
	MechamonConstructor(string _name) {
		name = _name;
	}
	string name;
};

struct Mechamon {
public:
	void setName(string newName) {
		name = newName;
	}
	string readName() {
		return name;
	}
	Mechamon(MechamonConstructor constructor) {
		name = constructor.name;
	}
private:
	string name;
};

map<string, MechamonConstructor> _mechamonConstructorList = {
	{ "mech1", MechamonConstructor("mech1") },
	{ "mech2", MechamonConstructor("mech2") },
	{ "mech3", MechamonConstructor("mech3") }
};

MechamonConstructor getConstructor(string mechamonName) {
	if (_mechamonConstructorList.contains(mechamonName)) {
		return _mechamonConstructorList[mechamonName];
	}
	return MechamonConstructor("FILLER");
}

vector<string> getPossibleMechamons() {
	vector<string> result = {};
	for (pair<string, MechamonConstructor> p : _mechamonConstructorList) {
		result.push_back(p.first);
	}
	return result;
}