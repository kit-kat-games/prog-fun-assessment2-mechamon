#include "main.h"

void printOpeningHeader() {
    textOutput.printBorderLine();
    textOutput.printEmptyLine();
    textOutput.printCentered("Welcome to the Mechamon monster battle simulation!");
    textOutput.printEmptyLine();
    textOutput.printBorderLine();
}

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
        textOutput.printEmptyLine();
        string infoChoice = getUserMultipleChoiceInput(possibleInputs, ("Please enter the number next to the mechamon you wish to view information about: " + choiceDisplayString + "."));
        textOutput.printEmptyLine();
        displayInfoOfType(mechamonMap[infoChoice]);
        textOutput.printEmptyLine();
    }
    return mechamonMap[choice];
}

bool createPlayer() {
    textOutput.print("Time to create your operator!");

    // Prompt player for their choice of name
    string oName = getUserStringInput("Please enter your operator's name. Enter 'RANDOM' for a random name instead: ");
    if (stringsEqualCaseInsensitive(oName, "RANDOM")) {
        vector<string> tempNames = VALID_OPERATOR_NAMES;
        shuffle(tempNames.begin(), tempNames.end(), rng);
        oName = tempNames[0];
    }
    Operator player = Operator(oName);
    textOutput.print("Your operator's name is " + player.readName() + ".");

    textOutput.printBorderLine();

    // Prompt player for their choice of mechamon, and assigning it its name
    textOutput.print("Time to create your mechamon!");
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

    textOutput.printBorderLine();
    textOutput.print("Your operator's name is " + player.readName() + ", and your mechamon's name is " + readCurMechamonName(player) +
        " of type " + readCurMechamonType(player) + ". Is this what you wish to play with? ");

    // Prompt user for whether they wish to create a new player or use the created one
    string choice = getUserMultipleChoiceInput({ "Y", "N" }, "Enter Y or N: ");
    if (stringsEqualCaseInsensitive(choice, "Y")) {
        textOutput.print("Player setup confirmed.");
    }
    else if (stringsEqualCaseInsensitive(choice, "N")) {
        textOutput.print("Resetting player, please create a new one.");
        textOutput.printBorderLine();
        return false;
    }
    textOutput.printBorderLine();
    return true;
}

void createOpponent() {
    // Randomly choose an opponent name
    vector<string> tempOpponentNames = VALID_OPERATOR_NAMES;
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

void resolveBattle() {
    Action pAction = ACTION_NA;
    Action oAction = ACTION_NA;
    int pPriority = -1;
    int oPriority = -1;
    bool playerFirst = true;

    while (true) {
        if (gameState.readBattleStage() == bSTAGE_BATTLERESULT) {
            return;
        }
        switch (gameState.readTurnStage()) {
        case tSTAGE_OUTOFBATTLE:
            textOutput.printCentered("Battle Started!");
            textOutput.printBorderLine();
            gameState.setTurnStage(tSTAGE_TURNSTART);
            break;
        case tSTAGE_TURNSTART:
            //
            //
            //
            gameState.setTurnStage(tSTAGE_ACTIONSELECTION);
            break;
        case tSTAGE_ACTIONSELECTION:
            resolveActionSelection(&pAction, &oAction, &gameState);
            gameState.setTurnStage(tSTAGE_ORDERCALC);
            break;
        case tSTAGE_ORDERCALC:
            // Decide the priority of each operator's action
            if (pAction == ACTION_ATTACK) {
                pPriority = gameState.getPlayerPtr()->getCurrentMechamonPtr()->readSpeed();
            }
            else {
                pPriority = getPriorityOfAction(pAction);
            }
            if (oAction == ACTION_ATTACK) {
                oPriority = gameState.getOpponentPtr()->getCurrentMechamonPtr()->readSpeed();
            }
            else {
                oPriority = getPriorityOfAction(oAction);
            }

            gameState.setTurnStage(tSTAGE_PROCESSACTION);
            break;
        case tSTAGE_PROCESSACTION:
            // Player go first, then opponent
            if (pPriority > oPriority) {
                playerFirst = true;
            } 
            // Randomly decide whether player or opponent goes first
            else if (pPriority == oPriority) {
                vector<char> opts = { 'p', 'o' };
                shuffle(opts.begin(), opts.end(), rng);
                if (opts[0] == 'p') {
                    playerFirst = true;
                }
                else {
                    playerFirst = false;
                }
            }
            // Opponent go first, then player
            else {
                playerFirst = false;
            }

            if (playerFirst) {
                resolveAction(pAction, gameState.getPlayerPtr(), gameState.getOpponentPtr(), &gameState);
                textOutput.printEmptyLine();
                resolveAction(oAction, gameState.getOpponentPtr(), gameState.getPlayerPtr(), &gameState);
            }
            else {
                resolveAction(oAction, gameState.getOpponentPtr(), gameState.getPlayerPtr(), &gameState);
                textOutput.printEmptyLine();
                resolveAction(pAction, gameState.getPlayerPtr(), gameState.getOpponentPtr(), &gameState);
            }

            textOutput.printEmptyLine();
            gameState.setTurnStage(tSTAGE_TURNEND);
            break;
        case tSTAGE_TURNEND:
            if (gameState.getPlayerPtr()->getCurrentMechamonPtr()->isDead() || gameState.getOpponentPtr()->getCurrentMechamonPtr()->isDead()) {
                gameState.setBattleStage(bSTAGE_BATTLERESULT);
                gameState.setTurnStage(tSTAGE_OUTOFBATTLE);
                return;
            }
            gameState.setTurnStage(tSTAGE_TURNSTART);
            break;
        }
    }
}

BattleStage resolveBattleResult() {
    // If all of the player's mechamons died, end the game and go to game result (can quit application or start another run)
    if (gameState.getPlayerPtr()->getCurrentMechamonPtr()->isDead()) {
        return bSTAGE_GAMERESULT;
    }

    // If either the player beat all of the opponent's mechamons, or either player ran, allow for either ending the game or finding a new battle
    if (gameState.getOpponentPtr()->getCurrentMechamonPtr()->isDead()) {
        textOutput.print("You beat " + gameState.readOpponentName() + "!");
    }
    else if (gameState.getPlayerPtr()->readRanFromBattle()) {
        textOutput.print("You ran... boo!");
    }
    else if (gameState.getOpponentPtr()->readRanFromBattle()) {
        textOutput.print(gameState.readOpponentName() + " ran! Good job scaring them off.");
    }

    // Have player decide whether to end the game or find another battle
    string choice = getUserMultipleChoiceInput({ "Y", "N" }, "Would you like to find another battle? Enter Y or N: ");
    if (stringsEqualCaseInsensitive(choice, "N")) {
        textOutput.print("Ending Current Game.");
        textOutput.printBorderLine();
        return bSTAGE_GAMERESULT;
    }
    textOutput.print("Healing your mechamons, finding you another opponent.");
    gameState.getPlayerPtr()->healAllMechamons();
    textOutput.printBorderLine();
    return bSTAGE_BATTLESETUP;
}

bool resolveGameResult() {
    string choice = getUserMultipleChoiceInput({ "Y", "N" }, "Would you like to play again? Enter Y or N: ");
    if (stringsEqualCaseInsensitive(choice, "Y")) {
        return true;
    }
    return false;
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
            textOutput.print("Your opponent is " + gameState.readOpponentName() + ". Their mechamon's name is " + readCurMechamonName(gameState.getOpponentPtr()) +
                " of type " + readCurMechamonType(gameState.getOpponentPtr()) + ".");
            textOutput.printBorderLine();
            gameState.setBattleStage(bSTAGE_INBATTLE);
            break;
        case bSTAGE_INBATTLE:
            resolveBattle();
            gameState.setBattleStage(bSTAGE_BATTLERESULT);
            break;
        case bSTAGE_BATTLERESULT:
            gameState.setBattleStage(resolveBattleResult());
            break;
        case bSTAGE_GAMERESULT:
            if (!resolveGameResult()) {
                textOutput.print("Application Closing. Thank you for playing!");
                gameRunning = false;
            }
            else {
                textOutput.print("Starting Setup for new Game.");
                textOutput.printBorderLine();
                createdPlayer = false;
                gameState.setBattleStage(bSTAGE_GAMESETUP);
            }
            break;
        }
    }
}