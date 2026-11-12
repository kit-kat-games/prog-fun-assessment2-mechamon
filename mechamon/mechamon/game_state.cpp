#pragma once
#include "game_state.h"

// Overloads of 2 functions - allow either an operator object, or a pointer to an operator object to be passed in
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