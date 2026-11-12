#include "text_input_handler.h"

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

		_printInputField(inputRequest);
	}
}

// string getUserStringInput(string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false)
string getUserStringInput(string inputRequest, bool mustHaveCharacters, bool mustHaveAlpha) {
	_printInputField(inputRequest);
	string input = _getLineStringInput(inputRequest, mustHaveCharacters, mustHaveAlpha);
	string lineContents = input + inputRequest;
	// Currently - Work out how to stop getline putting you on next line
	//printRightBorder(lineContents);
	return input;
}

// string getUserMultipleChoiceInput(vector<string> options, string inputRequest = "", bool caseMatters = false)
string getUserMultipleChoiceInput(vector<string> options, string inputRequest, bool caseMatters) {
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
		else {
			print("ERROR: That is not a valid choice. Please choose again.");
		}
	}
	return result;
}