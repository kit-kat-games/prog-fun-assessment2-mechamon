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

    string choice = "";
    vector<string> possibleInputsWithInfoChoice = possibleInputs;
    possibleInputsWithInfoChoice.push_back("INFO");
    while (true) {
        // INSERT A WAY TO VIEW DATA OF MECHAMON BEING CHOSEN 
        choice = getUserMultipleChoiceInput(possibleInputsWithInfoChoice, ("Please enter the number next to the mechamon you wish to choose: " + choiceDisplayString + ". Enter 'INFO' to see information about the choices."));
        if (!stringsEqualCaseInsensitive(choice, "INFO")) {
            // If not asking for info, a mechamon has been chosen
            break;
        }
        printEmptyLine();
        string infoChoice = getUserMultipleChoiceInput(possibleInputs, ("Please enter the number next to the mechamon you wish to view information about: " + choiceDisplayString + "."));
        printEmptyLine();
        displayMechamonInfo(mechamonMap[infoChoice]);
        printEmptyLine();
    }
    return mechamonMap[choice];
}

bool createPlayer() {
    print("Time to create your operator!");

    // Prompt player for their choice of name
    string oName = getUserStringInput("Please enter your operator's name: ");
    Operator player = Operator(oName);
    print("Your operator's name is " + player.readName() + ".");

    printBorderLine();

    // Prompt player for their choice of mechamon, and assigning it its name
    print("Time to create your mechamon!");
    string mType = getPlayerMechamonChoice();
    string mName = getUserStringInput("Please enter your mechamon's name. Enter 'RANDOM' for a random name instead: ");

    // If prompted, randomly select a name instead
    if (stringsEqualCaseInsensitive(mName, "RANDOM")) {
        vector<string> tempMechamonNames = VALID_MECHAMON_NAMES;
        shuffle(tempMechamonNames.begin(), tempMechamonNames.end(), rng);
        mName = tempMechamonNames[0];
    }

    // Create a mechamon based on the inputted data
    MechamonConstructor constructor = createMechamonConstructor(mType, mName);
    Mechamon mechamon = Mechamon(constructor);
    
    // Put Data into Game State
    player.addMechamonToList(mechamon);
    gameState.setPlayer(player);

    printBorderLine();
    print("Your operator's name is " + player.readName() + ", and your mechamon's name is " + readCurMechamonName(player) +
        " of type " + readCurMechamonType(player) + ". Is this what you wish to play with? ");

    // Prompt user for whether they wish to create a new player or use the created one
    string choice = getUserMultipleChoiceInput({ "Y", "N" }, "Enter Y or N: ");
    if (stringsEqualCaseInsensitive(choice, "Y")) {
        print("Player setup confirmed.");
    }
    else if (stringsEqualCaseInsensitive(choice, "N")) {
        print("Resetting player, please create a new one.");
        printBorderLine();
        return false;
    }
    printBorderLine();
    return true;
}

void createOpponent() {
    // Randomly choose an opponent name
    vector<string> tempOpponentNames = VALID_OPPONENT_NAMES;
    shuffle(tempOpponentNames.begin(), tempOpponentNames.end(), rng);
    string oName = tempOpponentNames[0];

    Operator opponent = Operator(oName);

    // Randomly choose a type of mechamon
    vector<string> tempMechamonTypes = getPossibleMechamonTypes();
    shuffle(tempMechamonTypes.begin(), tempMechamonTypes.end(), rng);
    string mType = tempMechamonTypes[0];

    // Randomly choose a name for the mechamon
    vector<string> tempMechamonNames = VALID_MECHAMON_NAMES;
    shuffle(tempMechamonNames.begin(), tempMechamonNames.end(), rng);
    string mName = tempMechamonNames[0];

    // Create a mechamon based on the randomly generated data
    MechamonConstructor constructor = createMechamonConstructor(mType, mName);
    Mechamon mechamon = Mechamon(constructor);

    // Put Data into Game State
    opponent.addMechamonToList(mechamon);
    gameState.setOpponent(opponent);
}

bool resolveBattle() {
    switch (gameState.readTurnStage()) {
    case tSTAGE_OUTOFBATTLE:
        printCentered("Battle Started!");
        printBorderLine();
        gameState.setTurnStage(tSTAGE_TURNSTART);
        break;
    case tSTAGE_TURNSTART:
        //
        //
        //
        gameState.setTurnStage(tSTAGE_MOVESELECTION);
        break;
    case tSTAGE_MOVESELECTION:
        //
        //
        //
        gameState.setTurnStage(tSTAGE_ORDERCALC);
        break;
    case tSTAGE_ORDERCALC:
        //
        //
        //
        gameState.setTurnStage(tSTAGE_PROCESSMOVE);
        break;
    case tSTAGE_PROCESSMOVE:
        //
        //
        //
        gameState.setTurnStage(tSTAGE_TURNEND);
        break;
    case tSTAGE_TURNEND:
        //
        //
        //
        gameState.setTurnStage(tSTAGE_TURNSTART);
        break;
    }
    return true;
}

int main()
{
    printOpeningHeader();

    // Booleans for gameplay loop
    bool createdPlayer = false;
    bool gameRunning = true;

    // Gameplay Loop
    while (gameRunning) {
        switch (gameState.readBattleStage()) {
        case bSTAGE_GAMESETUP:
            // Create the player
            while (!createdPlayer) {
                createdPlayer = createPlayer();
            }
            gameState.setBattleStage(bSTAGE_BATTLESETUP);
            break;
        case bSTAGE_BATTLESETUP:
            // Create a new opponent
            createOpponent();
            print("Your first opponent is " + gameState.readOpponentName() + ". Their mechamon's name is " + readCurMechamonName(gameState.getOpponentPtr()) +
                " of type " + readCurMechamonType(gameState.getOpponentPtr()) + ".");
            printBorderLine();
            gameState.setBattleStage(bSTAGE_INBATTLE);
            break;
        case bSTAGE_INBATTLE:
            bool battleResolved = resolveBattle();
            if (battleResolved) {
                gameState.setBattleStage(bSTAGE_BATTLERESULT);
            }
            break;
        }
    }
}