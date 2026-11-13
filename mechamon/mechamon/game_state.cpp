#pragma once
#include <string>
#include "game_state.h"

// Overloads of 2 functions - allow either an operator object, or a pointer to an operator object to be passed in
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