#pragma once
#include "generic_header.h"
#include "misc_funcs.h"
#include "text_output_handler.h"

// Status Flag For A Mechamon Would Be 0b0000'0000'0000'0000'0000
// Most right is the mask flags for what statuses are active
// Each chunk of 4 bits to the left of that represents the time remaining for its status
// Fe, say statusFlags = 0b0000'0110'0000'0000'0100
// Then the second status flag is active, and it has 6 turns left
const uint8_t STATUS_MASK_CLEAR = 0b0000;
const uint8_t STATUS_MASK_SLOWED = 0b0001;
const uint8_t STATUS_MASK_FROZEN = 0b0010;
const uint8_t STATUS_MASK_BURNING = 0b0100;
const uint8_t STATUS_MASK_STRENGTHENED = 0b1000;

struct Attack {
	string name = "";
	int damage = -1;
	uint8_t statusApplyMask = STATUS_MASK_CLEAR;
	Attack() {}
	Attack(string _name) {
		name = _name;
	}
	Attack(int _damage) {
		damage = _damage;
	}
	Attack(string _name, int _damage) {
		name = _name;
		damage = _damage;
	}
	Attack(int _damage, uint8_t _statusApplyMask) {
		damage = _damage;
		statusApplyMask = _statusApplyMask;
	}
	Attack(string _name, int _damage, uint8_t _statusApplyMask) {
		name = _name;
		damage = _damage;
		statusApplyMask = _statusApplyMask;
	}
};

struct MechamonConstructor {
public:
	string type = "";
	string name = "";
	int attack = -1;
	int health = -1;
	int speed = -1;
	vector<Attack> attackList = {};
	MechamonConstructor() {}
	MechamonConstructor(string _type) {
		type = _type;
	}
	MechamonConstructor(string _type, string _name) {
		type = _type;
		name = _name;
	}
	MechamonConstructor(string _type, string _name, int _attack, int _health, int _speed) {
		type = _type;
		name = _name;
		attack = _attack;
		health = _health;
		speed = _speed;
	}
	MechamonConstructor(string _type, string _name, int _attack, int _health, int _speed, vector<Attack> _attackList) {
		type = _type;
		name = _name;
		attack = _attack;
		health = _health;
		speed = _speed;
		attackList = _attackList;
	}
};

struct Mechamon {
public:
	void setName(string newName) {
		name = newName;
	}
	void dealDamage(int dmg) {
		health = max(health - dmg, 0);
	}
	void healDamage(int amt = -1) {
		if (amt > 0) {
			health = min(health + amt, maxHealth);
		}
		else {
			health = maxHealth;
		}
	}
	string readName() {
		return name;
	}
	string readType() {
		return type;
	}
	int readAttack() {
		return attack;
	}
	int readHealth() {
		return health;
	}
	int readSpeed() {
		return speed;
	}
	bool isDead() {
		return health <= 0;
	}
	vector<Attack>* getAttackListPtr() {
		return &attacklist;
	}
	Mechamon() {}
	Mechamon(MechamonConstructor constructor) {
		name = constructor.name;
		type = constructor.type;
		attack = constructor.attack;
		health = constructor.health;
		maxHealth = constructor.health;
		speed = constructor.speed;
		attacklist = constructor.attackList;
	}
private:
	string name = "";
	string type = "";
	int attack = -1;
	int health = -1;
	int maxHealth = -1;
	int speed = -1;
	vector<Attack> attacklist = {};
	uint64_t statusFlags = 0b0000'0000'0000'0000'0000;
};

vector<string> _mechamonTypesList = { "mech1", "mech2", "mech3", "mech4", "mech5", "mech6" };
map<string, MechamonConstructor> _typeConstructorMap = {
	{ "mech1", MechamonConstructor("mech1", "", 20, 50, 6, {Attack("Burning Punch", 10, (STATUS_MASK_BURNING | STATUS_MASK_STRENGTHENED))})},
	{ "mech2", MechamonConstructor("mech2", "", 25, 45, 6)},
	{ "mech3", MechamonConstructor("mech3", "", 25, 55, 3)},
	{ "mech4", MechamonConstructor("mech4", "", 10, 80, 3)},
	{ "mech5", MechamonConstructor("mech5", "", 15, 60, 5)},
	{ "mech6", MechamonConstructor("mech6", "", 15, 50, 8)},
};

MechamonConstructor createMechamonConstructor(string mechamonType, string instanceName = "") {
	if (!isWithin(mechamonType, _mechamonTypesList)) {
		return MechamonConstructor("NOTVALIDTYPE");
	}
	MechamonConstructor mConstructor = MechamonConstructor(_typeConstructorMap[mechamonType]);
	mConstructor.name = instanceName;
	return mConstructor;
}

vector<string> getPossibleMechamonTypes() {
	return _mechamonTypesList;
}

map<uint8_t, string> statusEffectNameMap = {
	{ STATUS_MASK_CLEAR, "N/A" },
	{ STATUS_MASK_SLOWED, "Slowed" },
	{ STATUS_MASK_FROZEN, "Frozen" },
	{ STATUS_MASK_BURNING, "Burning" },
	{ STATUS_MASK_STRENGTHENED, "Strengthened" },
};

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