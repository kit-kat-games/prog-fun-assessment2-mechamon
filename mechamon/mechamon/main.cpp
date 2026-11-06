#include "main.h"

GameState gameState;

void createPlayer() {
    print("Time to create your operator!"); 
    string oName = getUserStringInput("Please enter your operator's name: ");
    Operator player = Operator(oName);
    print("Your operator's name is " + player.readName() + ".");
    
    printBorderLine();

    print("Time to create your mechamon!");

    // Get Possible Mechamon Choices
    vector<string> possibleMechamons = getPossibleMechamons();
    for (string p : possibleMechamons) {
        print(p);
    }

    string mName = getUserStringInput("Please enter your mechamon's name: ");
    MechamonConstructor constructor = MechamonConstructor(mName);
    Mechamon mechamon = Mechamon(constructor);
    
    player.addMechamonToList(mechamon);
    gameState.setPlayer(player);

    print("Your mechamon's name is " + gameState.readPlayerMechamonName() + ".");

    printBorderLine();
}

int main()
{
    printOpeningHeader();
    createPlayer();
    
    print(getUserMultipleChoiceInput({ "A", "B", "C", "D" }, "Please choose one of the following: A, B, C or D."));
}