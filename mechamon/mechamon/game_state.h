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
	inline std::string readCurMechamonName(Operator oper) {
		return oper.getCurrentMechamonPtr()->readName();
	}
	inline std::string readCurMechamonName(Operator* oper) {
		return oper->getCurrentMechamonPtr()->readName();
	}
	inline std::string readCurMechamonType(Operator oper) {
		return oper.getCurrentMechamonPtr()->readType();
	}
	inline std::string readCurMechamonType(Operator* oper) {
		return oper->getCurrentMechamonPtr()->readType();
	}
private:
	TurnStage turnStage = tSTAGE_OUTOFBATTLE;
	BattleStage battleStage = bSTAGE_GAMESETUP;
	Operator player = Operator("NOTSETUP");
	Operator opponent = Operator("NOTSETUP");
};

<<<<<<< Updated upstream

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
=======
inline GameState* gameStatePtr;
>>>>>>> Stashed changes
