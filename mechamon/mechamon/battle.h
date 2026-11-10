#pragma once
#include "generic_header.h"
#include "misc_funcs.h"

enum MoveChoice {
	mCHOICE_ATTACK,
	mCHOICE_ITEM,
	mCHOICE_SWAP,
	mCHOICE_RUN,
	mCHOICE_NA,
};

map<MoveChoice, string> _moveChoiceInputMap = {
	{ mCHOICE_ATTACK, "A" },
	{ mCHOICE_ITEM, "I" },
	{ mCHOICE_SWAP, "S" },
	{ mCHOICE_RUN, "R" },
};

vector<string> getPossibleMoveChoiceInputs() {
	vector<string> result;
	for (const pair<MoveChoice, string>& p : _moveChoiceInputMap) {
		result.push_back(p.second);
	}
	return result;
}

MoveChoice getMoveChoiceOfStringInput(string input) {
	vector<string> possibleInputs;
	map<string, MoveChoice> inputMap;
	for (const pair<MoveChoice, string>& p : _moveChoiceInputMap) {
		possibleInputs.push_back(p.second);
		inputMap.insert_or_assign(p.second, p.first);
	}
	if (!isWithin(input, possibleInputs)) {
		return mCHOICE_NA;
	}
	return inputMap[input];
}