#pragma once
#include <string>
#include <stdint.h>
#include "mechamon.h"
#include "misc_funcs.h"

inline MechamonConstructor createMechamonConstructor(std::string mechamonType, std::string instanceName) {
	if (!isWithin(mechamonType, _mechamonTypesList)) {
		return MechamonConstructor();
	}
	MechamonConstructor mConstructor = MechamonConstructor(_typeConstructorMap[mechamonType]);
	mConstructor.name = instanceName;
	return mConstructor;
}

inline std::vector<std::string> getPossibleMechamonTypes() {
	return _mechamonTypesList;
}

inline std::string getStatusEffectString(uint8_t statusApplyMask) {
	std::string result = "";
	for (const std::pair<uint8_t, std::string>& p : _statusEffectNameMap) {
		std::cout << statusApplyMask << std::endl;
		std::cout << p.first << std::endl;
		if ((statusApplyMask & p.first) == statusApplyMask) {
			if (result != "") {
				result += ", ";
			}
			result += p.second;
		}
	}
	return result;
}

inline void displayInfoOfType(std::string type) {
	if (!isWithin(type, _mechamonTypesList)) {
		textOutputPtr->print(type + " is not a valid mechamon type.");
		return;
	}
	textOutputPtr->print("Type: " + type);
	textOutputPtr->print("ATK: " + std::to_string(_typeConstructorMap[type].attack));
	textOutputPtr->print("HP: " + std::to_string(_typeConstructorMap[type].health));
	textOutputPtr->print("SPD: " + std::to_string(_typeConstructorMap[type].speed));
}