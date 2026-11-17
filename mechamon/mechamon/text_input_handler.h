#pragma once
#include "generic_header.h"
#include "text_output_handler.h"
#include "misc_funcs.h"

void _printInputField(string inputRequest = "") {
	if (inputRequest != "") {
		print(inputRequest, true, false, false);
	}
}

string _getLineStringInput(string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false) {
	while (true) {
		string input;
		getline(cin, input);
		if (cin.fail()) {
			print("ERROR: That is not a string.");
		}
		else if (input == "") {
			print("ERROR: That is an empty string, please give an input with characters.");
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
					print("ERROR: There are no letters in that input, please give an input with letters.");
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
					print("ERROR: There are no characters in that input, please give an input with characters.");
					valid = false;
				}
			}
			if (valid) {
				return input;
			}
		}

<<<<<<< Updated upstream
		_printInputField(inputRequest);
=======
class TextInput {
public:
	std::string getUserInput(std::string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false, bool canBeEmpty = false) {
		_printInputField(inputRequest);
		std::string input = _getLineStringInput(inputRequest, mustHaveCharacters, mustHaveAlpha, canBeEmpty);
		std::string lineContents = input + inputRequest;
		// Currently - Work out how to stop getline putting you on next line
		//printRightBorder(lineContents);
		return input;
>>>>>>> Stashed changes
	}
}

string getUserStringInput(string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false) {
	_printInputField(inputRequest);
	string input = _getLineStringInput(inputRequest, mustHaveCharacters, mustHaveAlpha);
	string lineContents = input + inputRequest;
	// Currently - Work out how to stop getline putting you on next line
	//printRightBorder(lineContents);
	return input;
}

string getUserMultipleChoiceInput(vector<string> options, string inputRequest = "", bool caseMatters = false) {
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
		print(inputRequest);
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
<<<<<<< Updated upstream
		else {
			print("ERROR: That is not a valid choice. Please choose again.");
		}
	}
	return result;
}
=======
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
		textOutputPtr->print(inputRequest, true, false, false);
	}
	std::string _getLineStringInput(std::string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false, bool canBeEmpty = false) {
		while (true) {
			std::string input;
			getline(std::cin, input);
			if (std::cin.fail()) {
				textOutputPtr->print("ERROR: That is not a string.");
			}
			else if (input == "" && !canBeEmpty) {
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
>>>>>>> Stashed changes
