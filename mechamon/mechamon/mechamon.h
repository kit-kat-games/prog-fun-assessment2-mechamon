#pragma once
#include <vector>
#include <map>
#include "globals.h"
using namespace std;

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

struct MechamonConstructor;
inline MechamonConstructor createMechamonConstructor(string mechamonType, string instanceName = "");
inline vector<string> getPossibleMechamonTypes();
inline string getStatusEffectString(uint8_t statusApplyMask);
inline void displayInfoOfType(string type);

struct Attack {
	// Constructor Options
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
	
	// Variable Members
	string name = "";
	int damage = -1;
	uint8_t statusApplyMask = STATUS_MASK_CLEAR;
	
	//
	void displayInfo() {
		textOutputPtr->print("Name: " + name);
		textOutputPtr->print("DMG: " + to_string(damage));
		textOutputPtr->print("Status Effect: " + getStatusEffectString(statusApplyMask));
	}
};

struct MechamonConstructor {
	// Constructor Options
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
	
	// Variable Members
	string type = "";
	string name = "";
	int attack = -1;
	int health = -1;
	int speed = -1;
	vector<Attack> attackList = {};
};

struct Mechamon {
public:
	// Constructor Options
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

	// Set/Read/Get Methods
	void setName(string newName) {
		name = newName;
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
	vector<Attack>* getAttackListPtr() {
		return &attacklist;
	}
	bool isDead() {
		return health <= 0;
	}

	// Logic Methods
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
	void displayInfo() {
		textOutputPtr->print("Type: " + type);
		textOutputPtr->print("ATK: " + to_string(attack));
		textOutputPtr->print("HP: " + to_string(health));
		textOutputPtr->print("SPD: " + to_string(speed));
	}
private:
	// Variable Methods
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
	{ "mech1", MechamonConstructor("mech1", "", 20, 50, 6, {Attack("Burning Punch", 10, (STATUS_MASK_BURNING | STATUS_MASK_STRENGTHENED))}) },
	{ "mech2", MechamonConstructor("mech2", "", 25, 45, 6) },
	{ "mech3", MechamonConstructor("mech3", "", 25, 55, 3) },
	{ "mech4", MechamonConstructor("mech4", "", 10, 80, 3) },
	{ "mech5", MechamonConstructor("mech5", "", 15, 60, 5) },
	{ "mech6", MechamonConstructor("mech6", "", 15, 50, 8) },
};
map<uint8_t, string> _statusEffectNameMap = {
	{ STATUS_MASK_CLEAR, "N/A" },
	{ STATUS_MASK_SLOWED, "Slowed" },
	{ STATUS_MASK_FROZEN, "Frozen" },
	{ STATUS_MASK_BURNING, "Burning" },
	{ STATUS_MASK_STRENGTHENED, "Strengthened" },
};