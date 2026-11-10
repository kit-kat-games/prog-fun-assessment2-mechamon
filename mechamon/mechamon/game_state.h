#pragma once
#include "generic_header.h"
#include "operator.h"

enum TurnStage {
	tSTAGE_OUTOFBATTLE,
	tSTAGE_TURNSTART,
	tSTAGE_MOVESELECTION,
	tSTAGE_ORDERCALC,
	tSTAGE_PROCESSMOVE,
	tSTAGE_TURNEND,
};

enum BattleStage {
	bSTAGE_GAMESETUP,
	bSTAGE_BATTLESETUP,
	bSTAGE_INBATTLE,
	bSTAGE_BATTLERESULT,
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
	string readPlayerName() {
		return player.readName();
	}
	string readOpponentName() {
		return opponent.readName();
	}
private:
	TurnStage turnStage = tSTAGE_OUTOFBATTLE;
	BattleStage battleStage = bSTAGE_GAMESETUP;
	Operator player = Operator("NOTSETUP");
	Operator opponent = Operator("NOTSETUP");
};


string readCurMechamonName(Operator oper) {
	return oper.getCurrentMechamonPtr()->readName();
}

string readCurMechamonName(Operator* oper) {
	return oper->getCurrentMechamonPtr()->readName();
}

string readCurMechamonType(Operator oper) {
	return oper.getCurrentMechamonPtr()->readType();
}

string readCurMechamonType(Operator* oper) {
	return oper->getCurrentMechamonPtr()->readType();
}