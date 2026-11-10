#pragma once
#include "generic_header.h"
#include "text_output_handler.h"

void printOpeningHeader() {
    printBorderLine();
    printEmptyLine();
    printCentered("Welcome to the Mechamon monster battle simulation!");
    printEmptyLine();
    printBorderLine();
}
