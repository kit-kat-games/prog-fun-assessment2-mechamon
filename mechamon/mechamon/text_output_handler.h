#pragma once
#include <iostream>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <windows.h>
#include <vector>
#include <thread>
#include <chrono>

const int IN_TERMINAL_WIDTH = 120;
const char BORDER_CHAR = '*';
const int TYPING_INTERVAL = 25;
const int LINE_LENGTH_LIMIT = IN_TERMINAL_WIDTH - 4;

class TextOutput {
public:
	TextOutput() {
		hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
		default_attributes = consoleInfo.wAttributes;
		curTextColor = -1;
		allowColoredBorder = false;
	}
	
	void print(std::string str, bool inclLeftBorder = true, bool inclRightBorder = true, bool inclEndl = true) {
		if (str.length() <= LINE_LENGTH_LIMIT) {
			if (inclLeftBorder) { _printLeftBorder(); }
			std::cout << str;
			if (inclRightBorder) { _printRightBorder(str); }
			if (inclEndl) { std::cout << std::endl; }
		}
		else {
			std::vector<std::string> splitStrLines = _splitLongString(str);
			for (std::string s : splitStrLines) {
				print(s, inclLeftBorder, inclRightBorder, inclEndl);
			}
		}
	}
	void printCentered(std::string str, bool inclLeftBorder = true, bool inclRightBorder = true, bool inclEndl = true) {
		if (str.length() <= LINE_LENGTH_LIMIT) {
			int offset = ((IN_TERMINAL_WIDTH - str.length()) / 2) - 2;
			std::string strOuput = std::string(offset, ' ') + str;
			if (inclLeftBorder) { _printLeftBorder(); }
			std::cout << strOuput;
			if (inclRightBorder) { _printRightBorder(strOuput); }
			if (inclEndl) { std::cout << std::endl; }
		}
		else {
			std::vector<std::string> splitStrLines = _splitLongString(str);
			for (std::string s : splitStrLines) {
				printCentered(s, inclLeftBorder, inclRightBorder, inclEndl);
			}
		}
	}
	void printBorderLine() {
		std::cout << std::string(IN_TERMINAL_WIDTH, BORDER_CHAR) << std::endl;
	}
	void printEmptyLine() {
		_printLeftBorder();
		_printRightBorder("");
		std::cout << std::endl;
	}
	void printTyping(std::string str, bool inclLeftBorder = true, bool inclRightBorder = true, bool inclEndl = true) {
		if (str.length() <= LINE_LENGTH_LIMIT) {
			if (inclLeftBorder) { _printLeftBorder(); }
			for (char c : str) {
				std::cout << c;
				std::this_thread::sleep_for(std::chrono::milliseconds(TYPING_INTERVAL));
			}
			if (inclRightBorder) { _printRightBorder(str); }
			if (inclEndl) { std::cout << std::endl; }
		}
		else {
			std::vector<std::string> splitStrLines = _splitLongString(str);
			for (std::string s : splitStrLines) {
				printTyping(s, inclLeftBorder, inclRightBorder, inclEndl);
			}
		}
	}
	void printCenteredTyping(std::string str, bool inclLeftBorder = true, bool inclRightBorder = true, bool inclEndl = true) {
		if (str.length() <= LINE_LENGTH_LIMIT) {
			int offset = ((IN_TERMINAL_WIDTH - str.length()) / 2) - 2;
			std::string strOuput = std::string(offset, ' ') + str;
			if (inclLeftBorder) { _printLeftBorder(); }
			std::cout << std::string(offset, ' ');
			for (char c : str) {
				std::cout << c;
				std::this_thread::sleep_for(std::chrono::milliseconds(TYPING_INTERVAL));
			}
			if (inclRightBorder) { _printRightBorder(strOuput); }
			if (inclEndl) { std::cout << std::endl; }
		}
		else {
			std::vector<std::string> splitStrLines = _splitLongString(str);
			for (std::string s : splitStrLines) {
				printCenteredTyping(s, inclLeftBorder, inclRightBorder, inclEndl);
			}
		}
	}
	void setTextColor(int newColor) {
		SetConsoleTextAttribute(hConsole, newColor);
		curTextColor = newColor;
	}
	int resetTextColor() {
		int curColor = curTextColor;
		SetConsoleTextAttribute(hConsole, default_attributes);
		curTextColor = -1;
		return curColor;
	}
private:
	bool allowColoredBorder;

	// Stack Overflow did help in finding the correct api to use, as well as the general syntax for storing attributes and returning to the default.
	HANDLE hConsole;
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	WORD default_attributes;
	int curTextColor;

	void _printLeftBorder() {
		if (allowColoredBorder) {
			std::cout << BORDER_CHAR << " ";
		}
		else {
			int curColor = resetTextColor();
			std::cout << BORDER_CHAR << " ";
			setTextColor(curColor);
		}
	}
	void _printRightBorder(std::string lineContents) {
		int leftoverLine = IN_TERMINAL_WIDTH - lineContents.length() - 3;
		if (allowColoredBorder) {
			std::cout << std::string(leftoverLine, ' ');
			std::cout << BORDER_CHAR;
		}
		else {
			int curColor = resetTextColor();
			std::cout << std::string(leftoverLine, ' ');
			std::cout << BORDER_CHAR;
			setTextColor(curColor);
		}
	}
	std::vector<std::string> _splitLongString(std::string str) {
		std::vector<std::string> splitStrLines = {};
		std::string currentLine = "";
		std::string currentWord = "";
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

inline TextOutput* textOutputPtr;