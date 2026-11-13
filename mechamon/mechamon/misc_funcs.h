#pragma once
#include <string>

template <typename S, typename A>
inline bool isWithin(S searching, A structure) {
	for (S s : structure) {
		if (searching == s) {
			return true;
		}
	}
	return false;
}

inline bool stringsEqualCaseInsensitive(std::string strA, std::string strB) {
	std::string a = "";
	for (char c : strA) {
		a += std::tolower(c);
	}
	std::string b = "";
	for (char c : strB) {
		b += std::tolower(c);
	}
	bool stringsEqual = (a == b);
	return stringsEqual;
}