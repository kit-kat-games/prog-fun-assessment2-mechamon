#include "mechamon.h"

MechamonConstructor createMechamonConstructor(string mechamonType, string instanceName) {
	if (!isWithin(mechamonType, _mechamonTypesList)) {
		return MechamonConstructor();
	}
	MechamonConstructor mConstructor = MechamonConstructor(_typeConstructorMap[mechamonType]);
	mConstructor.name = instanceName;
	return mConstructor;
}

vector<string> getPossibleMechamonTypes() {
	return _mechamonTypesList;
}

string getStatusEffectString(uint8_t statusApplyMask) {
	string result = "";
	for (const pair<uint8_t, string>& p : statusEffectNameMap) {
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

void displayInfoOfType(string type) {
	if (!isWithin(type, _mechamonTypesList)) {
		print(type + " is not a valid mechamon type.");
		return;
	}
	print("Type: " + type);
	print("ATK: " + to_string(_typeConstructorMap[type].attack));
	print("HP: " + to_string(_typeConstructorMap[type].health));
	print("SPD: " + to_string(_typeConstructorMap[type].speed));
}

void displayInfoOfMechamon(Mechamon* mechamonPtr) {
	print("Type: " + mechamonPtr->readType());
	print("ATK: " + to_string(mechamonPtr->readAttack()));
	print("HP: " + to_string(mechamonPtr->readHealth()));
	print("SPD: " + to_string(mechamonPtr->readSpeed()));
}

void displayInfoOfAttack(Attack attack) {
	print("Name: " + attack.name);
	print("DMG: " + to_string(attack.damage));
	print("Status Effect: " + getStatusEffectString(attack.statusApplyMask));
}