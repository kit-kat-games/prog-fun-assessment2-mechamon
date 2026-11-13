#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "misc_funcs.h"
#include "text_output_handler.h"

class TextInput {
public:
	std::string getUserInput(std::string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false) {
		_printInputField(inputRequest);
		std::string input = _getLineStringInput(inputRequest, mustHaveCharacters, mustHaveAlpha);
		std::string lineContents = input + inputRequest;
		// Currently - Work out how to stop getline putting you on next line
		//printRightBorder(lineContents);
		return input;
	}
	std::string getUserMultipleChoiceInput(std::vector<std::string> options, std::string inputRequest = "", bool caseMatters = false) {
		std::string result = "";
		if (!caseMatters) {
			std::vector<std::string> temp = options;
			options.clear();
			for (std::string s : temp) {
				std::string option = "";
				for (char c : s) {
					option += std::tolower(c);
				}
				options.push_back(option);
			}
		}

		if (inputRequest != "") {
			textOutputPtr->print(inputRequest);
		}
		while (true) {
			std::string input = getUserInput("Please enter your choice of option: ");
			std::string casedInput = input;
			if (!caseMatters) {
				std::string temp = input;
				casedInput = "";
				for (char c : temp) {
					casedInput += std::tolower(c);
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
	void _printInputField(std::string inputRequest = "") {
		if (inputRequest != "") {
			textOutputPtr->print(inputRequest, true, false, false);
		}
	}
	std::string _getLineStringInput(std::string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false) {
		while (true) {
			std::string input;
			getline(std::cin, input);
			if (std::cin.fail()) {
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

inline TextInput* textInputPtr;