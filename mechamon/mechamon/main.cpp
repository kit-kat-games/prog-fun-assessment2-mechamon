#include "includes.h"

<<<<<<< Updated upstream
GameState gameState;
=======
void printOpeningHeader() {
    textOutputPtr->printBorderLine();
    textOutputPtr->printEmptyLine();
    textOutputPtr->printCenteredTyping("Welcome to the Mechamon monster battle simulation!");
    textOutputPtr->printEmptyLine();
    textOutputPtr->printBorderLine();
}
>>>>>>> Stashed changes

string getPlayerMechamonChoice() {
    // Get Possible Mechamon Choices
<<<<<<< Updated upstream
    vector<string> possibleMechamons = getPossibleMechamonTypes();
    vector<string> possibleInputs = {};
    map<string, string> mechamonMap = {};
    string choiceDisplayString = "";
=======
    std::vector<std::string> possibleMechamons = mechamonFuncsPtr->getPossibleMechamonTypes();
    std::vector<std::string> possibleInputs = {};
    std::map<std::string, std::string> mechamonMap = {};
    std::string choiceDisplayString = "";
>>>>>>> Stashed changes

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
<<<<<<< Updated upstream
        printEmptyLine();
        string infoChoice = getUserMultipleChoiceInput(possibleInputs, ("Please enter the number next to the mechamon you wish to view information about: " + choiceDisplayString + "."));
        printEmptyLine();
        displayInfoOfType(mechamonMap[infoChoice]);
        printEmptyLine();
=======
        textOutputPtr->printEmptyLine();
        std::string infoChoice = textInputPtr->getUserMultipleChoiceInput(possibleInputs, ("Please enter the number next to the mechamon you wish to view information about: " + choiceDisplayString + "."));
        textOutputPtr->printEmptyLine();
        mechamonFuncsPtr->displayInfoOfType(mechamonMap[infoChoice]);
        textOutputPtr->printEmptyLine();
>>>>>>> Stashed changes
    }
    return mechamonMap[choice];
}

bool createPlayer() {
    print("Time to create your operator!");

    // Prompt player for their choice of name
    string oName = getUserStringInput("Please enter your operator's name. Enter 'RANDOM' for a random name instead: ");
    if (stringsEqualCaseInsensitive(oName, "RANDOM")) {
        vector<string> tempNames = VALID_OPERATOR_NAMES;
        shuffle(tempNames.begin(), tempNames.end(), rng);
        oName = tempNames[0];
    }
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
    MechamonConstructor constructor = mechamonFuncsPtr->createMechamonConstructor(mType, mName);
    Mechamon mechamon = Mechamon(constructor);
    
    // Put Data into Game State
    player.addMechamonToList(mechamon);
    gameStatePtr->setPlayer(player);

<<<<<<< Updated upstream
    printBorderLine();
    print("Your operator's name is " + player.readName() + ", and your mechamon's name is " + readCurMechamonName(player) +
        " of type " + readCurMechamonType(player) + ". Is this what you wish to play with? ");
=======
    textOutputPtr->printBorderLine();
    textOutputPtr->print("Your operator's name is " + player.readName() + ", and your mechamon's name is " + gameStatePtr->readCurMechamonName(player) +
        " of type " + gameStatePtr->readCurMechamonType(player) + ". Is this what you wish to play with? ");
>>>>>>> Stashed changes

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
    vector<string> tempOpponentNames = VALID_OPERATOR_NAMES;
    shuffle(tempOpponentNames.begin(), tempOpponentNames.end(), rng);
    string oName = tempOpponentNames[0];

    Operator opponent = Operator(oName);

    // Randomly choose a type of mechamon
<<<<<<< Updated upstream
    vector<string> tempMechamonTypes = getPossibleMechamonTypes();
    shuffle(tempMechamonTypes.begin(), tempMechamonTypes.end(), rng);
    string mType = tempMechamonTypes[0];
=======
    std::vector<std::string> tempMechamonTypes = mechamonFuncsPtr->getPossibleMechamonTypes();
    std::shuffle(tempMechamonTypes.begin(), tempMechamonTypes.end(), rng);
    std::string mType = tempMechamonTypes[0];
>>>>>>> Stashed changes

    // Randomly choose a name for the mechamon
    vector<string> tempMechamonNames = VALID_MECHAMON_NAMES;
    shuffle(tempMechamonNames.begin(), tempMechamonNames.end(), rng);
    string mName = tempMechamonNames[0];

    // Create a mechamon based on the randomly generated data
    MechamonConstructor constructor = mechamonFuncsPtr->createMechamonConstructor(mType, mName);
    Mechamon mechamon = Mechamon(constructor);

    // Put Data into Game State
    opponent.addMechamonToList(mechamon);
    gameStatePtr->setOpponent(opponent);
}

void resolveBattle() {
    Action pAction = ACTION_NA;
    Action oAction = ACTION_NA;
    int pPriority = -1;
    int oPriority = -1;
    bool playerFirst = true;

    while (true) {
        if (gameStatePtr->readBattleStage() == bSTAGE_BATTLERESULT) {
            return;
        }
        switch (gameStatePtr->readTurnStage()) {
        case tSTAGE_OUTOFBATTLE:
<<<<<<< Updated upstream
            printCentered("Battle Started!");
            printBorderLine();
            gameState.setTurnStage(tSTAGE_TURNSTART);
=======
            textOutputPtr->printCentered("Battle Started!");
            textOutputPtr->printBorderLine();
            gameStatePtr->setTurnStage(tSTAGE_TURNSTART);
>>>>>>> Stashed changes
            break;
        case tSTAGE_TURNSTART:
            battlePtr->tickDownStatusEffectTimers();
            battlePtr->resolveTurnStartStatusEffects();
            gameStatePtr->setTurnStage(tSTAGE_ACTIONSELECTION);
            break;
        case tSTAGE_ACTIONSELECTION:
            battlePtr->resolveActionSelection(&pAction, &oAction);
            gameStatePtr->setTurnStage(tSTAGE_ORDERCALC);
            break;
        case tSTAGE_ORDERCALC:
            // Decide the priority of each operator's action
            if (pAction == ACTION_ATTACK) {
                pPriority = gameStatePtr->getPlayerPtr()->getCurrentMechamonPtr()->readSpeed();
            }
            else {
                pPriority = battlePtr->getPriorityOfAction(pAction);
            }
            if (oAction == ACTION_ATTACK) {
                oPriority = gameStatePtr->getOpponentPtr()->getCurrentMechamonPtr()->readSpeed();
            }
            else {
                oPriority = battlePtr->getPriorityOfAction(oAction);
            }
<<<<<<< Updated upstream

            gameState.setTurnStage(tSTAGE_PROCESSACTION);
=======
            gameStatePtr->setTurnStage(tSTAGE_PROCESSACTION);
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
                resolveAction(pAction, gameState.getPlayerPtr(), gameState.getOpponentPtr(), &gameState);
                printEmptyLine();
                resolveAction(oAction, gameState.getOpponentPtr(), gameState.getPlayerPtr(), &gameState);
            }
            else {
                resolveAction(oAction, gameState.getOpponentPtr(), gameState.getPlayerPtr(), &gameState);
                printEmptyLine();
                resolveAction(pAction, gameState.getPlayerPtr(), gameState.getOpponentPtr(), &gameState);
            }

            printEmptyLine();
            gameState.setTurnStage(tSTAGE_TURNEND);
=======
                battlePtr->resolveAction(pAction, gameStatePtr->getPlayerPtr(), gameStatePtr->getOpponentPtr());
                textOutputPtr->printEmptyLine();
                battlePtr->resolveAction(oAction, gameStatePtr->getOpponentPtr(), gameStatePtr->getPlayerPtr());
            }
            else {
                battlePtr->resolveAction(oAction, gameStatePtr->getOpponentPtr(), gameStatePtr->getPlayerPtr());
                textOutputPtr->printEmptyLine();
                battlePtr->resolveAction(pAction, gameStatePtr->getPlayerPtr(), gameStatePtr->getOpponentPtr());
            }

            textOutputPtr->printEmptyLine();
            gameStatePtr->setTurnStage(tSTAGE_TURNEND);
>>>>>>> Stashed changes
            break;
        case tSTAGE_TURNEND:
            if (gameStatePtr->getPlayerPtr()->getCurrentMechamonPtr()->isDead() || gameStatePtr->getOpponentPtr()->getCurrentMechamonPtr()->isDead()) {
                gameStatePtr->setBattleStage(bSTAGE_BATTLERESULT);
                gameStatePtr->setTurnStage(tSTAGE_OUTOFBATTLE);
                return;
            }
            battlePtr->resolveTurnEndStatusEffects();
            gameStatePtr->setTurnStage(tSTAGE_TURNSTART);
            break;
        }
    }
}

BattleStage resolveBattleResult() {
    // If all of the player's mechamons died, end the game and go to game result (can quit application or start another run)
    if (gameStatePtr->getPlayerPtr()->getCurrentMechamonPtr()->isDead()) {
        return bSTAGE_GAMERESULT;
    }

    // If either the player beat all of the opponent's mechamons, or either player ran, allow for either ending the game or finding a new battle
<<<<<<< Updated upstream
    if (gameState.getOpponentPtr()->getCurrentMechamonPtr()->isDead()) {
        print("You beat " + gameState.readOpponentName() + "!");
    }
    else if (gameState.getPlayerPtr()->readRanFromBattle()) {
        print("You ran... boo!");
    }
    else if (gameState.getOpponentPtr()->readRanFromBattle()) {
        print(gameState.readOpponentName() + " ran! Good job scaring them off.");
=======
    if (gameStatePtr->getOpponentPtr()->getCurrentMechamonPtr()->isDead()) {
        textOutputPtr->print("You beat " + gameStatePtr->readOpponentName() + "!");
    }
    else if (gameStatePtr->getPlayerPtr()->readRanFromBattle()) {
        textOutputPtr->print("You ran... boo!");
    }
    else if (gameStatePtr->getOpponentPtr()->readRanFromBattle()) {
        textOutputPtr->print(gameStatePtr->readOpponentName() + " ran! Good job scaring them off.");
>>>>>>> Stashed changes
    }

    // Have player decide whether to end the game or find another battle
    string choice = getUserMultipleChoiceInput({ "Y", "N" }, "Would you like to find another battle? Enter Y or N: ");
    if (stringsEqualCaseInsensitive(choice, "N")) {
        print("Ending Current Game.");
        printBorderLine();
        return bSTAGE_GAMERESULT;
    }
<<<<<<< Updated upstream
    print("Healing your mechamons, finding you another opponent.");
    gameState.getPlayerPtr()->healAllMechamons();
    printBorderLine();
=======
    textOutputPtr->print("Healing your mechamons, finding you another opponent.");
    gameStatePtr->getPlayerPtr()->healAllMechamons();
    textOutputPtr->printBorderLine();
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
=======
    TextOutput textOutput;
    textOutputPtr = &textOutput;

    TextInput textInput;
    textInputPtr = &textInput;

    GameState gameState;
    gameStatePtr = &gameState;

    Battle battle;
    battlePtr = &battle;

>>>>>>> Stashed changes
    printOpeningHeader();

    // Booleans for gameplay loop
    bool createdPlayer = false;
    bool gameRunning = true;

    // Wait for user to press enter
    textOutputPtr->printEmptyLine();
    textOutputPtr->printCenteredTyping("Press Enter to start!");
    textInputPtr->getUserInput("", false, false, true);
    textOutputPtr->printBorderLine();

    // Gameplay Loop
    while (gameRunning) {
        switch (gameStatePtr->readBattleStage()) {
        case bSTAGE_GAMESETUP:
            // Create the player
            while (!createdPlayer) {
                createdPlayer = createPlayer();
            }
            gameStatePtr->setBattleStage(bSTAGE_BATTLESETUP);
            break;
        case bSTAGE_BATTLESETUP:
            // Create a new opponent
            createOpponent();
<<<<<<< Updated upstream
            print("Your opponent is " + gameState.readOpponentName() + ". Their mechamon's name is " + readCurMechamonName(gameState.getOpponentPtr()) +
                " of type " + readCurMechamonType(gameState.getOpponentPtr()) + ".");
            printBorderLine();
            gameState.setBattleStage(bSTAGE_INBATTLE);
=======
            textOutputPtr->print("Your opponent is " + gameStatePtr->readOpponentName() + ". Their mechamon's name is " + gameStatePtr->readCurMechamonName(gameStatePtr->getOpponentPtr()) +
                " of type " + gameStatePtr->readCurMechamonType(gameStatePtr->getOpponentPtr()) + ".");
            textOutputPtr->printBorderLine();
            gameStatePtr->setBattleStage(bSTAGE_INBATTLE);
>>>>>>> Stashed changes
            break;
        case bSTAGE_INBATTLE:
            resolveBattle();
            gameStatePtr->setBattleStage(bSTAGE_BATTLERESULT);
            break;
        case bSTAGE_BATTLERESULT:
            gameStatePtr->setBattleStage(resolveBattleResult());
            break;
        case bSTAGE_GAMERESULT:
            if (!resolveGameResult()) {
                print("Application Closing. Thank you for playing!");
                gameRunning = false;
            }
            else {
                print("Starting Setup for new Game.");
                printBorderLine();
                createdPlayer = false;
                gameStatePtr->setBattleStage(bSTAGE_GAMESETUP);
            }
            break;
        }
    }
}