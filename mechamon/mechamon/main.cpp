#include "includes.h"

GameState gameState;

string getPlayerMechamonChoice() {
    // Get Possible Mechamon Choices
    vector<string> possibleMechamons = getPossibleMechamonTypes();
    vector<string> possibleInputs = {};
    map<string, string> mechamonMap = {};
    string choiceDisplayString = "";

    for (int i = 0; i < possibleMechamons.size(); i++) {
        string iString = to_string(i);
        choiceDisplayString += (possibleMechamons[i] + " [" + iString + "]");
        possibleInputs.push_back(iString);
        
        if (i != possibleMechamons.size() - 1) {
            choiceDisplayString += ", ";
        }
    }

    for (int i = 0; i < possibleInputs.size(); i++) {
        mechamonMap.insert_or_assign(possibleInputs[i], possibleMechamons[i]);
    }

    string choice = getUserMultipleChoiceInput(possibleInputs, ("Please enter the number next to the mechamon you wish to choose: " + choiceDisplayString));

    return mechamonMap[choice];
}

void createPlayer() {
    print("Time to create your operator!");
    string oName = getUserStringInput("Please enter your operator's name: ");
    Operator player = Operator(oName);
    print("Your operator's name is " + player.readName() + ".");

    printBorderLine();

    print("Time to create your mechamon!");
    string mType = getPlayerMechamonChoice();

    string mName = getUserStringInput("Please enter your mechamon's name: ");
    MechamonConstructor constructor = createMechamonConstructor(mType, mName);
    Mechamon mechamon = Mechamon(constructor);
    
    // Put Data into Game State
    player.addMechamonToList(mechamon);
    gameState.setPlayer(player);

    printBorderLine();
}

void createOpponent() {
    random_device rd;
    //default_random_engine rng{ rd() };
    mt19937 rng{ rd() };

    shuffle(VALID_OPPONENT_NAMES.begin(), VALID_OPPONENT_NAMES.end(), rng);
    Operator opponent = Operator(VALID_OPPONENT_NAMES[0]);
    gameState.setOpponent(opponent);
}

int main()
{
    printOpeningHeader();
    bool creatingPlayer = true;
    while (creatingPlayer) {
        createPlayer();

        print("Your operator's name is " + gameState.readPlayerName() + ", and your mechamon's name is " + readCurMechamonName(*gameState.getPlayerPtr()) +
                    " of type " + readCurMechamonType(*gameState.getPlayerPtr()) + ". Is this what you wish to play with? ");

        string choice = getUserMultipleChoiceInput({ "Y", "N" }, "Enter Y or N: ");
        if (stringsEqualCaseInsensitive(choice, "Y")) {
            print("Player setup confirmed.");
            creatingPlayer = false;
        }
        else if (stringsEqualCaseInsensitive(choice, "N")) {
            print("Resetting player, please create a new one.");
        }
        printBorderLine();
    }

    bool gameRunning = true;
    while (gameRunning) {
        if (gameState.readBattleStage() != bSTAGE_INBATTLE) {
            switch (gameState.readBattleStage())
                case bSTAGE_GAMESETUP:
                    createOpponent();
                    cout << gameState.readOpponentName() << endl;
        }
    }
}