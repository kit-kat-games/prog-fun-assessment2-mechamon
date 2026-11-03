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

map<string, MechamonConstructor> mechamonList = {
	{ "Aerial", MechamonConstructor("Aerial") },
	{ "Lfrith", MechamonConstructor("Lfrith") },
	{ "Pharact", MechamonConstructor("Pharact")}
};



MechamonConstructor getConstructor(string mechamonName) {
	return MechamonConstructor("fILLER");
}