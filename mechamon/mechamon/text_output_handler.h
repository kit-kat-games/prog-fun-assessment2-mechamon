#pragma once
#include "generic_header.h"
#include "consts.h"

class TextOutput {
public:
	TextOutput() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		default_attributes = consoleInfo.wAttributes;
		curTextColor = -1;
		allowColoredBorder = false;
	}
	
	static inline void print(string str, bool inclLeftBorder = true, bool inclRightBorder = true, bool inclEndl = true) {
		if (str.length() <= LINE_LENGTH_LIMIT) {
			if (inclLeftBorder) { _printLeftBorder(); }
			cout << str;
			if (inclRightBorder) { _printRightBorder(str); }
			if (inclEndl) { cout << endl; }
		}
		else {
			vector<string> splitStrLines = _splitLongString(str);
			for (string s : splitStrLines) {
				print(s, inclLeftBorder, inclRightBorder, inclEndl);
			}
		}
	}
	static inline void printCentered(string str, bool inclLeftBorder = true, bool inclRightBorder = true, bool inclEndl = true) {
		if (str.length() <= LINE_LENGTH_LIMIT) {
			int offset = ((IN_TERMINAL_WIDTH - str.length()) / 2) - 2;
			string strOuput = string(offset, ' ') + str;
			if (inclLeftBorder) { _printLeftBorder(); }
			cout << strOuput;
			if (inclRightBorder) { _printRightBorder(strOuput); }
			if (inclEndl) { cout << endl; }
		}
		else {
			vector<string> splitStrLines = _splitLongString(str);
			for (string s : splitStrLines) {
				printCentered(s, inclLeftBorder, inclRightBorder, inclEndl);
			}
		}
	}
	static inline void printBorderLine() {
		cout << string(IN_TERMINAL_WIDTH, BORDER_CHAR) << endl;
	}
	static inline void printEmptyLine() {
		_printLeftBorder();
		_printRightBorder("");
		cout << endl;
	}
	static inline void printTyping(string str, bool inclLeftBorder = true, bool inclRightBorder = true, bool inclEndl = true) {
		if (str.length() <= LINE_LENGTH_LIMIT) {
			if (inclLeftBorder) { _printLeftBorder(); }
			for (char c : str) {
				cout << c;
				this_thread::sleep_for(chrono::milliseconds(TYPING_INTERVAL));
			}
			if (inclRightBorder) { _printRightBorder(str); }
			if (inclEndl) { cout << endl; }
		}
		else {
			vector<string> splitStrLines = _splitLongString(str);
			for (string s : splitStrLines) {
				printTyping(s, inclLeftBorder, inclRightBorder, inclEndl);
			}
		}
	}
	static inline void printCenteredTyping(string str, bool inclLeftBorder = true, bool inclRightBorder = true, bool inclEndl = true) {
		if (str.length() <= LINE_LENGTH_LIMIT) {
			int offset = ((IN_TERMINAL_WIDTH - str.length()) / 2) - 2;
			string strOuput = string(offset, ' ') + str;
			if (inclLeftBorder) { _printLeftBorder(); }
			cout << string(offset, ' ');
			for (char c : str) {
				cout << c;
				this_thread::sleep_for(chrono::milliseconds(TYPING_INTERVAL));
			}
			if (inclRightBorder) { _printRightBorder(strOuput); }
			if (inclEndl) { cout << endl; }
		}
		else {
			vector<string> splitStrLines = _splitLongString(str);
			for (string s : splitStrLines) {
				printCenteredTyping(s, inclLeftBorder, inclRightBorder, inclEndl);
			}
		}
	}
private:
	static bool allowColoredBorder;

	// Stack Overflow did help in finding the correct api to use, as well as the general syntax for storing attributes and returning to the default.
	static HANDLE hConsole;
	static CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	static WORD default_attributes;
	static int curTextColor;

	static inline void setTextColor(int newColor) {
		SetConsoleTextAttribute(hConsole, newColor);
		curTextColor = newColor;
	}
	static inline int resetTextColor() {
		int curColor = curTextColor;
		SetConsoleTextAttribute(hConsole, default_attributes);
		curTextColor = -1;
		return curColor;
	}
	static inline void _printLeftBorder() {
		if (allowColoredBorder) {
			cout << BORDER_CHAR << " ";
		}
		else {
			int curColor = resetTextColor();
			cout << BORDER_CHAR << " ";
			setTextColor(curColor);
		}
	}
	static inline void _printRightBorder(string lineContents) {
		int leftoverLine = IN_TERMINAL_WIDTH - lineContents.length() - 3;
		if (allowColoredBorder) {
			cout << string(leftoverLine, ' ');
			cout << BORDER_CHAR;
		}
		else {
			int curColor = resetTextColor();
			cout << string(leftoverLine, ' ');
			cout << BORDER_CHAR;
			setTextColor(curColor);
		}
	}
	static inline vector<string> _splitLongString(string str) {
		vector<string> splitStrLines = {};
		string currentLine = "";
		string currentWord = "";
		for (char c : str) {
			if (c != ' ') {
				currentWord += c;
			}
			else {
				if (currentLine.length() + currentWord.length() + 1 < LINE_LENGTH_LIMIT) {
					if (currentLine != "") {
						currentLine += (" " + currentWord);
					}
					else {
						currentLine += currentWord;
					}
					currentWord = "";
				}
				else {
					splitStrLines.push_back(currentLine);
					currentLine = currentWord;
					currentWord = "";
				}
			}
		}

		if (currentLine != "" || currentWord != "") {
			splitStrLines.push_back(currentLine + " " + currentWord);
		}
		return splitStrLines;
	}
};