#pragma once
#include "generic_header.h"
#include "misc_funcs.h"
#include "game_state.h"
#include "mechamon.h"
#include "text_input_handler.h"
#include "random.h"

const uint8_t ITEM_ACTION_PRIORITY = 3;
const uint8_t RUN_ACTION_PRIORITY = 9;
const uint8_t SWAP_ACTION_PRIORITY = 5;

enum Action {
	ACTION_ATTACK,
	ACTION_ITEM,
	ACTION_SWAP,
	ACTION_RUN,
	ACTION_NA,
};

map<Action, string> _actionInputMap = {
	{ ACTION_ATTACK, "A" },
	{ ACTION_ITEM, "I" },
	{ ACTION_SWAP, "S" },
	{ ACTION_RUN, "R" },
};
string actionChoicesDisplayString = "ATTACK [A], ITEM [I], SWAP [S], RUN [R]";

vector<string> getPossibleActionInputs();
int getPriorityOfAction(Action action);
void resolveActionSelection(Action* pActionPtr, Action* oActionPtr, GameState* gameStatePtr);
void resolveAction(Action action, Operator* userPtr, Operator* targetPtr, GameState* gameStatePtr);