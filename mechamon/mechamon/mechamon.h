#pragma once
#include "generic_header.h"

struct Mechamon {
public:
	void setName(string newName) {
		name = newName;
	}
	string readName() {
		return name;
	}
	Mechamon(string _name) {
		name = _name;
	}
private:
	string name;
};