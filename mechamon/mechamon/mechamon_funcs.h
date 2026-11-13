#pragma once
#include <string>
#include <stdint.h>
#include "misc_funcs.h"
#include "mechamon_classes.h"
#include "mechamon_data.h"

class MechamonFuncs {
public:
	inline MechamonConstructor createMechamonConstructor(std::string mechamonType, std::string instanceName = "") {
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
	inline void displayInfo(Attack attack) {
		textOutputPtr->print("Name: " + attack.name);
		textOutputPtr->print("DMG: " + std::to_string(attack.damage));
		textOutputPtr->print("Status Effect: " + getStatusEffectString(attack.statusApplyMask));
	}
	inline void displayInfo(Attack* attackPtr) {
		textOutputPtr->print("Name: " + attackPtr->name);
		textOutputPtr->print("DMG: " + std::to_string(attackPtr->damage));
		textOutputPtr->print("Status Effect: " + getStatusEffectString(attackPtr->statusApplyMask));
	}
	inline void displayInfo(Mechamon mechamon) {
		textOutputPtr->print("Type: " + mechamon.readType());
		textOutputPtr->print("ATK: " + std::to_string(mechamon.readAttack()));
		textOutputPtr->print("HP: " + std::to_string(mechamon.readHealth()));
		textOutputPtr->print("SPD: " + std::to_string(mechamon.readSpeed()));
	}
	inline void displayInfo(Mechamon* mechamonPtr) {
		textOutputPtr->print("Type: " + mechamonPtr->readType());
		textOutputPtr->print("ATK: " + std::to_string(mechamonPtr->readAttack()));
		textOutputPtr->print("HP: " + std::to_string(mechamonPtr->readHealth()));
		textOutputPtr->print("SPD: " + std::to_string(mechamonPtr->readSpeed()));
	}
private:

};

inline MechamonFuncs* mechamonFuncsPtr;