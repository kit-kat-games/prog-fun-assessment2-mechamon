#pragma once
#include <stdint.h>
#include <vector>
#include <map>
#include <string>
#include "mechamon_classes.h"

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

inline std::vector<std::string> _mechamonTypesList = { "mech1", "mech2", "mech3", "mech4", "mech5", "mech6" };
inline std::map<std::string, MechamonConstructor> _typeConstructorMap = {
	{ "mech1", MechamonConstructor("mech1", "", 20, 50, 6, {Attack("Burning Punch", 10, (STATUS_MASK_BURNING | STATUS_MASK_STRENGTHENED))}) },
	{ "mech2", MechamonConstructor("mech2", "", 25, 45, 6) },
	{ "mech3", MechamonConstructor("mech3", "", 25, 55, 3) },
	{ "mech4", MechamonConstructor("mech4", "", 10, 80, 3) },
	{ "mech5", MechamonConstructor("mech5", "", 15, 60, 5) },
	{ "mech6", MechamonConstructor("mech6", "", 15, 50, 8) },
};
inline std::map<uint8_t, std::string> _statusEffectNameMap = {
	{ STATUS_MASK_CLEAR, "N/A" },
	{ STATUS_MASK_SLOWED, "Slowed" },
	{ STATUS_MASK_FROZEN, "Frozen" },
	{ STATUS_MASK_BURNING, "Burning" },
	{ STATUS_MASK_STRENGTHENED, "Strengthened" },
};