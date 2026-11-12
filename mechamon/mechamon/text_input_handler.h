#pragma once
#include "generic_header.h"
#include "text_output_handler.h"
#include "misc_funcs.h"

string getUserStringInput(string inputRequest = "", bool mustHaveCharacters = true, bool mustHaveAlpha = false);
string getUserMultipleChoiceInput(vector<string> options, string inputRequest = "", bool caseMatters = false);