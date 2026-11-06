#pragma once
#include "generic_header.h"

template <typename S, typename A>
bool isWithin(S searching, A structure) {
	for (S s : structure) {
		if (searching == s) {
			return true;
		}
	}
	return false;
}