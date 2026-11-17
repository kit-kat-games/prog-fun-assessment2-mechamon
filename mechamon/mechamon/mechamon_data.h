#pragma once
#include <vector>
#include <map>
#include <string>
#include "mechamon_classes.h"
#include "mechamon_status_data.h"

inline std::vector<std::string> _mechamonTypesList = { "mech1", "mech2", "mech3", "mech4", "mech5", "mech6" };
inline std::map<std::string, MechamonConstructor> _typeConstructorMap = {
	{ "mech1", MechamonConstructor("mech1", "", 20, 50, 6, {
		Attack("Burning Punch", 10, { 
			Status(STATUS_EFFECT_BURNING, STATUS_TARGET_ENEMY_MECHAMON, 3),
			Status(STATUS_EFFECT_STRENGTHENED, STATUS_TARGET_SELF, 1),
			}) 
		}) 
	},
	{ "mech2", MechamonConstructor("mech2", "", 25, 45, 6, {
		Attack("Burning Punch", 10, {
			Status(STATUS_EFFECT_BURNING, STATUS_TARGET_ENEMY_MECHAMON, 3),
			Status(STATUS_EFFECT_STRENGTHENED, STATUS_TARGET_SELF, 1),
			})
		})
	},
	{ "mech3", MechamonConstructor("mech3", "", 25, 55, 3, {
		Attack("Burning Punch", 10, {
			Status(STATUS_EFFECT_BURNING, STATUS_TARGET_ENEMY_MECHAMON, 3),
			Status(STATUS_EFFECT_STRENGTHENED, STATUS_TARGET_SELF, 1),
			})
		})
	},
	{ "mech4", MechamonConstructor("mech4", "", 10, 80, 3, {
		Attack("Burning Punch", 10, {
			Status(STATUS_EFFECT_BURNING, STATUS_TARGET_ENEMY_MECHAMON, 3),
			Status(STATUS_EFFECT_STRENGTHENED, STATUS_TARGET_SELF, 1),
			})
		})
	},
	{ "mech5", MechamonConstructor("mech5", "", 15, 60, 5, {
		Attack("Burning Punch", 10, {
			Status(STATUS_EFFECT_BURNING, STATUS_TARGET_ENEMY_MECHAMON, 3),
			Status(STATUS_EFFECT_STRENGTHENED, STATUS_TARGET_SELF, 1),
			})
		})
	},
	{ "mech6", MechamonConstructor("mech6", "", 15, 50, 8, {
		Attack("Burning Punch", 10, {
			Status(STATUS_EFFECT_BURNING, STATUS_TARGET_ENEMY_MECHAMON, 3),
			Status(STATUS_EFFECT_STRENGTHENED, STATUS_TARGET_SELF, 1),
			})
		})
	},
};