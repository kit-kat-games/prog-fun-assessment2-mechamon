#pragma once
#include "generic_header.h"
#include "gameplay_loop.h"
#include "operator.h"

struct GameState {
public:
	void setTurnStage(TurnStage newTurnStage) {
		turnStage = newTurnStage;
	} 
	void setBattleStage(BattleStage newBattleStage) {
		battleStage = newBattleStage;
	}
	TurnStage readTurnStage() {
		return turnStage;
	}
	BattleStage readBattleStage() {
		return battleStage;
	}
	void setPlayer(Operator* newPlayerPtr) {
		playerPtr = newPlayerPtr;
	}
	void setOpponent(Operator* newOpponentPtr) {
		opponentPtr = newOpponentPtr;
	}
	Operator* getPlayerPtr() {
		return playerPtr;
	}
	Operator* getOpponentPtr() {
		return opponentPtr;
	}
private:
	TurnStage turnStage = tSTAGE_OUTOFBATTLE;
	BattleStage battleStage = bSTAGE_GAMESETUP;
	Operator* playerPtr = nullptr;
	Operator* opponentPtr = nullptr;
};