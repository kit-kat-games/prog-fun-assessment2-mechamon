#pragma once
#include "operator.h"
#include "generic_header.h"

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
	inline void setTurnStage(TurnStage newTurnStage) {
		turnStage = newTurnStage;
	} 
	inline void setBattleStage(BattleStage newBattleStage) {
		battleStage = newBattleStage;
	}
	inline TurnStage readTurnStage() {
		return turnStage;
	}
	inline BattleStage readBattleStage() {
		return battleStage;
	}
	inline void setPlayer(Operator newPlayer) {
		player = newPlayer;
	}
	inline void setOpponent(Operator newOpponent) {
		opponent = newOpponent;
	}
	inline Operator* getPlayerPtr() {
		return &player;
	}
	inline Operator* getOpponentPtr() {
		return &opponent;
	}
	inline string readPlayerName() {
		return player.readName();
	}
	inline string readOpponentName() {
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