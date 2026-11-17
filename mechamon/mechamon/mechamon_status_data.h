#pragma once
#include <stdint.h>
#include <map>

enum StatusEffect {
	STATUS_EFFECT_CLEAR,
	STATUS_EFFECT_SLOWED,
	STATUS_EFFECT_FROZEN,
	STATUS_EFFECT_BURNING,
	STATUS_EFFECT_STRENGTHENED,
};

enum StatusTarget {
	STATUS_TARGET_SELF,
	STATUS_TARGET_ENEMY_MECHAMON,
};

inline std::map<StatusEffect, std::string> _statusEffectNameMap = {
	{ STATUS_EFFECT_CLEAR, "N/A" },
	{ STATUS_EFFECT_SLOWED, "Slowed" },
	{ STATUS_EFFECT_FROZEN, "Frozen" },
	{ STATUS_EFFECT_BURNING, "Burning" },
	{ STATUS_EFFECT_STRENGTHENED, "Strengthened" },
};

inline std::vector<StatusEffect> startOfTurnStatusEffects = {
	STATUS_EFFECT_BURNING,
};

inline std::vector<StatusEffect> endOfTurnStatusEffects = {

};

bool effectCanStack(StatusEffect statusEffect) {
	return false;
}

