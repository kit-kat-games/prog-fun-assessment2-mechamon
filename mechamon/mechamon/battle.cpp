#pragma once
#include <random>
#include <algorithm>
#include "battle.h"
#include "misc_funcs.h"
#include "globals.h"

vector<string> getPossibleActionInputs() {
	vector<string> result;
	for (const pair<Action, string>& p : _actionInputMap) {
		result.push_back(p.second);
	}
	return result;
}

Action _getActionOfInput(string input) {
	string temp = input;
	input = "";
	for (char c : temp) {
		input += toupper(c);
	}

	vector<string> possibleInputs;
	map<string, Action> inputMap;
	for (const pair<Action, string>& p : _actionInputMap) {
		possibleInputs.push_back(p.second);
		inputMap.insert_or_assign(p.second, p.first);
	}
	if (!isWithin(input, possibleInputs)) {
		return ACTION_NA;
	}
	return inputMap[input];
}

int getPriorityOfAction(Action action) {
	if (action == ACTION_ATTACK) {
		return 0; // Should be handled externally - Will be equal to mechamon speed or move priority itself
	}
	if (action == ACTION_SWAP) {
		return SWAP_ACTION_PRIORITY;
	}
	if (action == ACTION_ITEM) {
		return ITEM_ACTION_PRIORITY;
	}
	if (action == ACTION_RUN) {
		return RUN_ACTION_PRIORITY;
	}
	return -1;
}

void _resolveViewInfo(GameState* gameStatePtr) {
	textOutputPtr->printEmptyLine();
	textOutputPtr->print("Please choose what you wish to view information on. Enter the character next to the choice you wish to view info on.");
	textOutputPtr->print("View Player Mechamon info [P]");
	textOutputPtr->print("View Opponent Mechamon info [O]");
	textOutputPtr->print("View a list of your Mechamons [M]");
	textOutputPtr->print("View a list of your Attacks [A]");
	textOutputPtr->print("View a list of your Items [I]");
	string input = textInputPtr->getUserMultipleChoiceInput({ "P", "O", "M", "A", "I" }, "Enter the character next to the choice you wish to view info on.");
	textOutputPtr->printEmptyLine();

	if (stringsEqualCaseInsensitive(input, "P")) {
		gameStatePtr->getPlayerPtr()->getCurrentMechamonPtr()->displayInfo();
	}
	else if (stringsEqualCaseInsensitive(input, "O")) {
		gameStatePtr->getOpponentPtr()->getCurrentMechamonPtr()->displayInfo();
	}
	else if (stringsEqualCaseInsensitive(input, "M")) {
		textOutputPtr->print("Your Mechamon:");
		vector<Mechamon>* mechamonListPtr = gameStatePtr->getPlayerPtr()->getMechamonListPtr();
		for (Mechamon mechamon : *mechamonListPtr) {
			textOutputPtr->print(mechamon.readName());
		}
	}
	else if (stringsEqualCaseInsensitive(input, "A")) {
		vector<Attack>* attackListPtr = gameStatePtr->getPlayerPtr()->getCurrentMechamonPtr()->getAttackListPtr();
		for (int i = 0; i < attackListPtr->size(); i++) {
			vector<Attack> attackList = *attackListPtr;
			attackList[i].displayInfo();
			if (i != attackList.size() - 1) {
				textOutputPtr->printEmptyLine();
			}
		}
	}
	else if (stringsEqualCaseInsensitive(input, "I")) {

	}

	textOutputPtr->printEmptyLine();
}

void resolveActionSelection(Action* pActionPtr, Action* oActionPtr, GameState* gameStatePtr) {
	vector<string> possibleActions = getPossibleActionInputs();
	vector<string> playerActions = possibleActions;
	playerActions.push_back("?");

	while (true) {
		// Player chooses an action to do
		string input = textInputPtr->getUserMultipleChoiceInput(playerActions, ("Please choose what you wish to do this turn, enter the character next to the choice you wish to make. " +
			actionChoicesDisplayString + ", VIEW INFO [?]"));
		if (input != "?") {
			*pActionPtr = _getActionOfInput(input);
			break;
		}
		else {
			_resolveViewInfo(gameStatePtr);
		}
	}

	// Opponent randomly chooses an action to do - COULD INSERT AI FOR SMART MOVE CHOICE
	shuffle(possibleActions.begin(), possibleActions.end(), rng);
	*oActionPtr = _getActionOfInput(possibleActions[0]);

	textOutputPtr->printEmptyLine();
}

void _resolveAttackAction(Operator* userPtr, Operator* targetPtr) {
	string userName = userPtr->readName();
	string targName = targetPtr->readName();
	string userMechName = readCurMechamonName(userPtr);
	string targMechName = readCurMechamonName(targetPtr);

	textOutputPtr->print(userName + "'s mechamon " + userMechName + " attacks!");

	int dmg = userPtr->getCurrentMechamonPtr()->readAttack();
	targetPtr->getCurrentMechamonPtr()->dealDamage(dmg);

	textOutputPtr->print(userMechName + " deals " + to_string(dmg) + " damage to " + targMechName + ".");

	int hp = targetPtr->getCurrentMechamonPtr()->readHealth();
	if (!targetPtr->getCurrentMechamonPtr()->isDead()) {
		textOutputPtr->print(targMechName + " is now at " + to_string(hp) + "HP.");
	}
	else {
		textOutputPtr->print(targMechName + " faints!");
	}
}

void resolveAction(Action action, Operator* userPtr, Operator* targetPtr, GameState* gameStatePtr) {
	switch (action) {
	case ACTION_ATTACK:
		_resolveAttackAction(userPtr, targetPtr);
		break;
	case ACTION_ITEM:
		textOutputPtr->print(userPtr->readName() + " uses an item!");
		break;
	case ACTION_SWAP:
		textOutputPtr->print(userPtr->readName() + " swaps mechamons!");
		break;
	case ACTION_RUN:
		textOutputPtr->print(userPtr->readName() + " runs... boo!");
		userPtr->setRanFromBattle(true);
		gameStatePtr->setBattleStage(bSTAGE_BATTLERESULT);
		gameStatePtr->setTurnStage(tSTAGE_OUTOFBATTLE);
		break;
	}
}