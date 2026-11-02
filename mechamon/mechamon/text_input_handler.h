#pragma once
#include "generic_header.h"
#include "text_output_handler.h"

void printInputField(string inputRequest = "") {
	printLeftBorder();
	cout << inputRequest;
}

string getLineStringInput(string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false) {
	while (true) {
		string input;
		getline(cin, input);
		if (cin.fail()) {
			cerr << "ERROR: That is not a string." << endl;
		}
		else if (input == "") {
			cerr << "ERROR: That is an empty string, please give an input with characters." << endl;
		}
		else {
			bool valid = true;
			if (mustHaveAlpha) {
				bool noAlpha = true;
				for (char c : input) {
					if (isalpha(c)) {
						noAlpha = false;
					}
				}
				if (noAlpha) {
					cerr << "ERROR: There are no letters in that input, please give an input with letters." << endl;
					valid = false;
				}
			}
			if (mustHaveCharacters) {
				bool noCharacters = true;
				for (char c : input) {
					if (c != ' ') {
						noCharacters = false;
					}
				}
				if (noCharacters) {
					cerr << "ERROR: There are no characters in that input, please give an input with characters." << endl;
					valid = false;
				}
			}
			if (valid) {
				return input;
			}
		}

		printInputField(inputRequest);
	}
}

string getUserStringInput(string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false) {
	printInputField(inputRequest);
	string input = getLineStringInput(inputRequest, mustHaveCharacters, mustHaveAlpha);
	string lineContents = input + inputRequest;
	// Currently - Work out how to stop getline putting you on next line
	//printRightBorder(lineContents);
	return input;
}