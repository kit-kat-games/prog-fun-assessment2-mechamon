#pragma once
#include "generic_header.h"
#include "operator.h"

enum TurnStage {
	tSTAGE_OUTOFBATTLE,
	tSTAGE_TURNSTART,
	tSTAGE_ACTIONSELECTION,
	tSTAGE_ORDERCALC,
	tSTAGE_PROCESSACTION,
	tSTAGE_TURNEND,
};

enum BattleStage {
	bSTAGE_GAMESETUP,
	bSTAGE_BATTLESETUP,
	bSTAGE_INBATTLE,
	bSTAGE_BATTLERESULT,
	bSTAGE_GAMERESULT,
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
	Operator player = Operator();
	Operator opponent = Operator();
};


// Overloads of 2 functions - allow either an operator object, or a pointer to an operator object to be passed in
string readCurMechamonName(Operator oper);
string readCurMechamonName(Operator* oper);
string readCurMechamonType(Operator oper);
string readCurMechamonType(Operator* oper);