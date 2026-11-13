#pragma once
#include <string>
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
	inline std::string readPlayerName() {
		return player.readName();
	}
	inline std::string readOpponentName() {
		return opponent.readName();
	}
private:
	TurnStage turnStage = tSTAGE_OUTOFBATTLE;
	BattleStage battleStage = bSTAGE_GAMESETUP;
	Operator player = Operator();
	Operator opponent = Operator();
};

// Overloads of 2 functions - allow either an operator object, or a pointer to an operator object to be passed in
inline std::string readCurMechamonName(Operator oper);
inline std::string readCurMechamonName(Operator* oper);
inline std::string readCurMechamonType(Operator oper);
inline std::string readCurMechamonType(Operator* oper);