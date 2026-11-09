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

bool stringsEqualCaseInsensitive(string strA, string strB) {
	string a = "";
	for (char c : strA) {
		a += tolower(c);
	}
	string b = "";
	for (char c : strB) {
		b += tolower(c);
	}
	bool stringsEqual = (a == b);
	return stringsEqual;
}