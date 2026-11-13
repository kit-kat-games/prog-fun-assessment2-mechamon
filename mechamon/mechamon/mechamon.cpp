#pragma once
#include "mechamon.h"

inline MechamonConstructor createMechamonConstructor(string mechamonType, string instanceName) {
	if (!isWithin(mechamonType, _mechamonTypesList)) {
		return MechamonConstructor();
	}
	MechamonConstructor mConstructor = MechamonConstructor(_typeConstructorMap[mechamonType]);
	mConstructor.name = instanceName;
	return mConstructor;
}

inline vector<string> getPossibleMechamonTypes() {
	return _mechamonTypesList;
}

inline string getStatusEffectString(uint8_t statusApplyMask) {
	string result = "";
	for (const pair<uint8_t, string>& p : _statusEffectNameMap) {
		cout << statusApplyMask << endl;
		cout << p.first << endl;
		if ((statusApplyMask & p.first) == statusApplyMask) {
			if (result != "") {
				result += ", ";
			}
			result += p.second;
		}
	}
	return result;
}

inline void displayInfoOfType(string type) {
	if (!isWithin(type, _mechamonTypesList)) {
		textOutputPtr->print(type + " is not a valid mechamon type.");
		return;
	}
	textOutputPtr->print("Type: " + type);
	textOutputPtr->print("ATK: " + to_string(_typeConstructorMap[type].attack));
	textOutputPtr->print("HP: " + to_string(_typeConstructorMap[type].health));
	textOutputPtr->print("SPD: " + to_string(_typeConstructorMap[type].speed));
}