#pragma once
#include <vector>
#include <map>
#include <string>
#include <stdint.h>
#include "text_output_handler.h"
#include "mechamon_status_data.h"

struct Status {
	StatusEffect effect;
	StatusTarget target;
	unsigned int turnsLeft;
};

struct Attack {
	// Constructor Options
	Attack() {}
	Attack(std::string _name) {
		name = _name;
	}
	Attack(int _damage) {
		damage = _damage;
	}
	Attack(std::string _name, int _damage) {
		name = _name;
		damage = _damage;
	}
	Attack(int _damage, std::vector<Status> _statusApplyList) {
		damage = _damage;
		statusApplyList = _statusApplyList;
	}
	Attack(std::string _name, int _damage, std::vector<Status> _statusApplyList) {
		name = _name;
		damage = _damage;
		statusApplyList = _statusApplyList;
	}

	// Variable Members
	std::string name = "";
	int damage = -1;
	std::vector<Status> statusApplyList;
};

struct MechamonConstructor {
	// Constructor Options
	MechamonConstructor() {}
	MechamonConstructor(std::string _type) {
		type = _type;
	}
	MechamonConstructor(std::string _type, std::string _name) {
		type = _type;
		name = _name;
	}
	MechamonConstructor(std::string _type, std::string _name, int _attack, int _health, int _speed) {
		type = _type;
		name = _name;
		attack = _attack;
		health = _health;
		speed = _speed;
	}
	MechamonConstructor(std::string _type, std::string _name, int _attack, int _health, int _speed, std::vector<Attack> _attackList) {
		type = _type;
		name = _name;
		attack = _attack;
		health = _health;
		speed = _speed;
		attackList = _attackList;
	}

	// Variable Members
	std::string type = "";
	std::string name = "";
	int attack = -1;
	int health = -1;
	int speed = -1;
	std::vector<Attack> attackList = {};
};

class Mechamon {
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
	void setName(std::string newName) {
		name = newName;
	}
	std::string readName() {
		return name;
	}
	std::string readType() {
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
	std::vector<Attack>* getAttackListPtr() {
		return &attacklist;
	}
	bool isDead() {
		return health <= 0;
	}
	bool isUnderEffect(StatusEffect effect) {
		for (Status* statusPtr : statusPtrList) {
			if (statusPtr->effect == effect) {
				return true;
			}
		}
		return false;
	}
	std::vector<Status*>* getStatusPtrListPtr() {
		return &statusPtrList;
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
	bool applyStatus(Status status) {
		bool copyExists = false;
		for (Status* s : statusPtrList) {
			if (s->effect == status.effect) {
				if (s->turnsLeft >= status.turnsLeft && !effectCanStack(status.effect)) {
					return false;
				}
				copyExists = true;
			}
		}
		if (copyExists && !effectCanStack(status.effect)) {
			for (Status* s : statusPtrList) {
				if (s->effect == status.effect) {
					s->turnsLeft = status.turnsLeft;
					return true;
				}
			}
		}
		statusPtrList.push_back(&status);
		return true;
	}
private:
	// Variable Methods
	std::string name = "";
	std::string type = "";
	int attack = -1;
	int health = -1;
	int maxHealth = -1;
	int speed = -1;
	std::vector<Attack> attacklist = {};
	std::vector<Status*> statusPtrList = {};
};
