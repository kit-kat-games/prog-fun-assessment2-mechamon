#pragma once
#include "generic_header.h"
#include "text_output_handler.h"
#include "misc_funcs.h"
#include "globals.h"

class TextInput {
public:
	static inline string getUserStringInput(string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false) {
		_printInputField(inputRequest);
		string input = _getLineStringInput(inputRequest, mustHaveCharacters, mustHaveAlpha);
		string lineContents = input + inputRequest;
		// Currently - Work out how to stop getline putting you on next line
		//printRightBorder(lineContents);
		return input;
	}
	static inline string getUserMultipleChoiceInput(vector<string> options, string inputRequest = "", bool caseMatters = false) {
		string result = "";
		if (!caseMatters) {
			vector<string> temp = options;
			options.clear();
			for (string s : temp) {
				string option = "";
				for (char c : s) {
					option += tolower(c);
				}
				options.push_back(option);
			}
		}

		if (inputRequest != "") {
			textOutputPtr->print(inputRequest);
		}
		while (true) {
			string input = getUserStringInput("Please enter your choice of option: ");
			string casedInput = input;
			if (!caseMatters) {
				string temp = input;
				casedInput = "";
				for (char c : temp) {
					casedInput += tolower(c);
				}
			}
			if (isWithin(casedInput, options)) {
				result = input;
				break;
			}
			else {
				textOutputPtr->print("ERROR: That is not a valid choice. Please choose again.");
			}
		}
		return result;
	}
private:
	static inline void _printInputField(string inputRequest = "") {
		if (inputRequest != "") {
			textOutputPtr->print(inputRequest, true, false, false);
		}
	}
	static inline string _getLineStringInput(string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false) {
		while (true) {
			string input;
			getline(cin, input);
			if (cin.fail()) {
				textOutputPtr->print("ERROR: That is not a string.");
			}
			else if (input == "") {
				textOutputPtr->print("ERROR: That is an empty string, please give an input with characters.");
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
						textOutputPtr->print("ERROR: There are no letters in that input, please give an input with letters.");
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
						textOutputPtr->print("ERROR: There are no characters in that input, please give an input with characters.");
						valid = false;
					}
				}
				if (valid) {
					return input;
				}
			}

			_printInputField(inputRequest);
		}
	}
};