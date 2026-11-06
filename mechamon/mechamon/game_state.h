#pragma once
#include "generic_header.h"
#include "operator.h"

enum TurnStage {
	tSTAGE_TURNSTART,
	tSTAGE_MOVESELECTION,
	tSTAGE_ORDERCALC,
	tSTAGE_MOVEPROCESS,
	tSTAGE_TURNEND,
	tSTAGE_OUTOFBATTLE,
};

enum BattleStage {
	bSTAGE_BATTLESETUP,
	bSTAGE_INBATTLE,
	bSTAGE_BATTLERESULT,
	bSTAGE_FINDINGBATTLE,
	bSTAGE_GAMESETUP,
};

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
	void setPlayer(Operator newPlayer) {
		player = newPlayer;
	}
	void setOpponent(Operator newOpponent) {
		opponent = newOpponent;
	}
	Operator* getPlayerPtr() {
		return &player;
	}
	Operator* getOpponentPtr() {
		return &opponent;
	}
	string readPlayerMechamonName() {
		return player.getCurrentMechamonPtr()->readName();
	}
	string readOpponentMechamonName() {
		return opponent.getCurrentMechamonPtr()->readName();
	}
private:
	TurnStage turnStage = tSTAGE_OUTOFBATTLE;
	BattleStage battleStage = bSTAGE_GAMESETUP;
	Operator player = Operator("NOTSETUP");
	Operator opponent = Operator("NOTSETUP");
};