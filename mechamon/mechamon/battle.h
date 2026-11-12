#pragma once
#include "generic_header.h"
#include "misc_funcs.h"
#include "game_state.h"
#include "mechamon.h"

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

vector<string> getPossibleActionInputs() {
	vector<string> result;
	for (const pair<Action, string>& p : _actionInputMap) {
		result.push_back(p.second);
	}
	return result;
}

Action getActionOfInput(string input) {
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
}

void resolveViewInfo(GameState* gameStatePtr) {
	printEmptyLine();
	print("Please choose what you wish to view information on. Enter the character next to the choice you wish to view info on.");
	print("View Player Mechamon info [P]");
	print("View Opponent Mechamon info [O]");
	print("View a list of your Mechamons [M]");
	print("View a list of your Attacks [A]");
	print("View a list of your Items [I]");
	string input = getUserMultipleChoiceInput({ "P", "O", "M", "A", "I" }, "Enter the character next to the choice you wish to view info on.");
	printEmptyLine();

	if (stringsEqualCaseInsensitive(input, "P")) {
		displayInfoOfMechamon(gameStatePtr->getPlayerPtr()->getCurrentMechamonPtr());
	}
	else if (stringsEqualCaseInsensitive(input, "O")) {
		displayInfoOfMechamon(gameStatePtr->getOpponentPtr()->getCurrentMechamonPtr());
	}
	else if (stringsEqualCaseInsensitive(input, "M")) {
		print("Your Mechamon:");
		vector<Mechamon>* mechamonListPtr = gameStatePtr->getPlayerPtr()->getMechamonListPtr();
		for (Mechamon mechamon : *mechamonListPtr) {
			print(mechamon.readName());
		}
	}
	else if (stringsEqualCaseInsensitive(input, "A")) {
		vector<Attack>* attackListPtr = gameStatePtr->getPlayerPtr()->getCurrentMechamonPtr()->getAttackListPtr();
		for (int i = 0; i < attackListPtr->size(); i++) {
			vector<Attack> attackList = *attackListPtr;
			displayInfoOfAttack(attackList[i]);
			if (i != attackList.size() - 1) {
				printEmptyLine();
			}
		}
	}
	else if (stringsEqualCaseInsensitive(input, "I")) {

	}

	printEmptyLine();
}

void resolveActionSelection(Action* pActionPtr, Action* oActionPtr, GameState* gameStatePtr) {
	vector<string> possibleActions = getPossibleActionInputs();
	vector<string> playerActions = possibleActions;
	playerActions.push_back("?");

	while (true) {
		// Player chooses an action to do
		string input = getUserMultipleChoiceInput(playerActions, ("Please choose what you wish to do this turn, enter the character next to the choice you wish to make. " +
			actionChoicesDisplayString + ", VIEW INFO [?]"));
		if (input != "?") {
			*pActionPtr = getActionOfInput(input);
			break;
		}
		else {
			resolveViewInfo(gameStatePtr);
		}
	}

	// Opponent randomly chooses an action to do - COULD INSERT AI FOR SMART MOVE CHOICE
	shuffle(possibleActions.begin(), possibleActions.end(), rng);
	*oActionPtr = getActionOfInput(possibleActions[0]);

	printEmptyLine();
}

void resolveAttackAction(Operator* userPtr, Operator* targetPtr) {
	string userName = userPtr->readName();
	string targName = targetPtr->readName();
	string userMechName = readCurMechamonName(userPtr);
	string targMechName = readCurMechamonName(targetPtr);

	print(userName + "'s mechamon " + userMechName + " attacks!");

	int dmg = userPtr->getCurrentMechamonPtr()->readAttack();
	targetPtr->getCurrentMechamonPtr()->dealDamage(dmg);

	print(userMechName + " deals " + to_string(dmg) + " damage to " + targMechName + ".");

	int hp = targetPtr->getCurrentMechamonPtr()->readHealth();
	if (!targetPtr->getCurrentMechamonPtr()->isDead()) {
		print(targMechName + " is now at " + to_string(hp) + "HP.");
	}
	else {
		print(targMechName + " faints!");
	}
}

void resolveAction(Action action, Operator* userPtr, Operator* targetPtr, GameState* gameStatePtr) {
	switch (action) {
	case ACTION_ATTACK:
		resolveAttackAction(userPtr, targetPtr);
		break;
	case ACTION_ITEM:
		print(userPtr->readName() + " uses an item!");
		break;
	case ACTION_SWAP:
		print(userPtr->readName() + " swaps mechamons!");
		break;
	case ACTION_RUN:
		print(userPtr->readName() + " runs... boo!");
		userPtr->setRanFromBattle(true);
		gameStatePtr->setBattleStage(bSTAGE_BATTLERESULT);
		gameStatePtr->setTurnStage(tSTAGE_OUTOFBATTLE);
		break;
	}
}