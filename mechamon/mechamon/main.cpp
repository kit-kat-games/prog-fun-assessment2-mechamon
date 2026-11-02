#include "main.h"

GameState gameState;

Operator createPlayer() {
    print("Time to create your operator!"); 

    string name = getUserStringInput("Please enter your operator's name: ");

    Operator player = Operator(name);
    return player;
}

Mechamon choosePlayerMechamon() {
    MechamonConstructor constructor = MechamonConstructor("Aerial");
    Mechamon mechamon = Mechamon(constructor);
    return mechamon;
}
int main()
{
    printOpeningHeader();
    Operator player = createPlayer();
    print("Your operator's name is " + player.readName());

    cout << mech1 << endl;
}