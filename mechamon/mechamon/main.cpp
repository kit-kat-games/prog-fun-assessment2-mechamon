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

    print("What would you like to do next?");
    setTextColor(23);
    printCentered("The text color has now been changed, and this text is now centered.");
    resetTextColor();
    print("The text color has been reset, and the following will be a really long piece of text for testing text splitting.");
    print("Lorem Ipsum is simply dummy text of the printing and typesetting industry. Lorem Ipsum has been the industry's standard dummy text ever since 1966, when designers at Letraset and James Mosley, the librarian at St Bride Printing Library in London, took a 1914 Cicero translation and scrambled it to make dummy text for Letraset's Body Type sheets. It has survived not only many decades, but also the leap into electronic typesetting, remaining essentially unchanged. It was popularised thanks to these sheets and more recently with desktop publishing software like Aldus PageMaker and Microsoft Word including versions of Lorem Ipsum.");
}