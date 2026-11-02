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

/*
Operator suletta = Operator("Suletta");
Mechamon aerial = Mechamon("Aerial");
suletta.addMechamonToList(aerial);
print(suletta.getCurrentMechamonPtr()->readName());

setTextColor(13);
printCentered("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since 1966, when designers at Letraset and James Mosley, the librarian at St Bride Printing Library in London, took a 1914 Cicero translation and scrambled it to make dummy text for Letraset's Body Type sheets. It has survived not only many decades, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised thanks to these sheets and more recently with desktop publishing software like Aldus PageMaker and Microsoft Word including versions of Lorem Ipsum.");
int prevColor = resetTextColor();
print("Hi");
setTextColor(prevColor);
print("Hi again");

resetTextColor();

Operator miorine = Operator("Miorine");
Mechamon aerialRebuilt = Mechamon("Aerial Rebuild");
miorine.addMechamonToList(aerialRebuilt);
gameState.setPlayer(&suletta);
print(gameState.getPlayerPtr()->readName());
gameState.setPlayer(&miorine);
print(gameState.getPlayerPtr()->getCurrentMechamonPtr()->readName());
*/