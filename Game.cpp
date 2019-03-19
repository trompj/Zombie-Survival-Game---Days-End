/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Game class combines all elements of the game into one functional program. Creates all menu outputs and
 * contains all map/player pointer objects. Game class runs a zombie survival game in which player must find objects
 * and avoid getting killed by zombies in the process to save his colony.
 * Variables: timeToDeath: Step counter until the end of the game when player loses if objectives are still not met.
 * currentMap: Map pointer to the map that player is currently in.
 * outdoors: Map pointer to outdoors level.
 * groceryStore: Map pointer to groceryStore level.
 * outdoorRecSupplier: Map pointer to the outdoor rec supplier map.
 * finalMap: Map pointer to the final map location (Field)
 * player: Player pointer to the player object in game.
 * Functions: Constructor sets up Game object by setting timeToDeath, allocating space for all maps, setting currentMap to outdoors,
 * allocating space to player, place player on currentMap, and call addDoors function to manually add linked doors
 * between maps.
 * Destructor deletes all instances of Map that was dynamically allocated.
 * runGame - Primary controller for game, runs all menu options and combines functionality. If user starts playing game,
 * menu prints allowing user to reset game when either user elects to quit or game ends due to loss or win.
 * movePlayer - Controller to allow for user selection for player movement on board. Prompts user for input of
 * direction to move and moves player piece in that direction. Returns boolean value for exit game. True to exit,
 * false to keep playing.
 * controlsDisplay - Output game controls to terminal for user viewing.
 * interactObject - If player elects to engage with a Space object, function is called to interact with object.
 * Function outputs and accepts/validates direction of object to interact with and performs interaction with object.
 * changeMaps - If moving through door linked to another map, change map location of player as movement and set player
 * in the new map location. Takes Space pointer as parameter.
 * addDoors - Add/link doors between maps on game to allow for traversal between maps within the world.
 * startMenu - Allow user to select to start or exit game. Return boolean value for user selection.
 * gameDesc - Outputs information/introduction of game and its premise.
 * outdoorDesc - Describes the outdoor map each time the map is changed to outdoors.
 * groceryStoreDesc - Describes the grocery store map each time the map is changed to grocery store.
 * recSupplierDesc - Describes the recreational supplier map each time the map is changed to rec supplier.
 * finalFieldDesc - Describes the final field map, each time the final map is entered.
 * resetMenu - Allow user to select reset game from scratch. Returns boolean value for user selection.
*/

#include "Game.hpp"

//Sets up Game object by setting timeToDeath, allocating space for all maps, setting currentMap to outdoors, allocating
//space to player, place player on currentMap, and call addDoors function to manually add linked doors between maps.
Game::Game() {
    //Set step limit for game until loss
    timeToDeath = 800;

    //Space locations setup - Outdoors (store fronts)
    outdoors = new Outdoors("Outside");

    //Space locations setup - Grocery store
    groceryStore = new GroceryStore("Grocery Store");

    //Space locations setup - Outdoor rec supplier
    outdoorRecSupplier = new OutdoorRecSupplier("Outdoor Recreational Supplier");

    //Space locations setup - Final map
    finalMap = new Field("Field");

    //Add doors to maps with map links
    addDoors();

    //Set current map to outdoors for start of game
    currentMap = outdoors;

    //Set player and location
    player = new Player("player", currentMap->getStartRow(), currentMap->getStartCol());

    //Set player in map
    currentMap->setPlayerLocation(player, player->getRows(), player->getCols());
}

//Free all dynamically allocated memory - deletes all instances of Map that was dynamically allocated.
Game::~Game() {
    delete outdoors;
    delete groceryStore;
    delete outdoorRecSupplier;
    delete finalMap;
}

//Primary controller for game, runs all menu options and combines functionality.
void Game::runGame() {
    bool playGame = false;
    bool resetGame = true;

    playGame = startMenu();
    std::cout << std::endl;

    do {
        if (playGame) {
            //Output description of game
            gameDesc();
            std::cout << std::endl;

            //Output description of initial map (outdoors)
            outdoorDesc();
            std::cout << std::endl;

            while (playGame) {
                //Draw current map
                currentMap->drawMap();

                //Allow user to move player during turn, displays controls and accepts/validates selection.
                //Moves player in direction selected.
                playGame = movePlayer();

                //Move zombies in all maps
                outdoors->moveZombies();
                groceryStore->moveZombies();
                outdoorRecSupplier->moveZombies();
                finalMap->moveZombies();

                //Check surroundings around player, if player is near a zombie, player is attacked (player attack check occurs
                //twice, once when zombie moves and once after zombie has moved).
                currentMap->checkZombies(player);

                timeToDeath--;

                //Check for player alive status
                if (!player->getAlive()) {
                    //Draw current map to show user contact with zombie
                    currentMap->drawMap();

                    std::cout << std::endl << "GAME OVER\nPlayer was overcome by a zombie and has fallen!" << std::endl;
                    playGame = false;
                } else if (player->getWin()) {
                    std::cout << std::endl
                              << "GAME WON!\nYou successfully retrieved the medicine for your group. You all live" <<
                              " to fight another day.\nYou make it back to your colony and are welcomed with open arms "
                              <<
                              "as the hero you are." << std::endl;
                    playGame = false;
                }

                    //Check turn counter, if no turns are left, game ends. Set playGame to false.
                else if (timeToDeath <= 0) {
                    std::cout << std::endl << "GAME OVER\n" <<
                              "You did not receive the medicine in time to save your group!" << std::endl;
                    playGame = false;
                }
            }

            //Ask user if they would like to reset the game and start new or quit
            resetGame = resetMenu();

            if (resetGame) {
                playGame = true;
                //Delete all current game aspects and free memory.
                delete outdoors;
                delete groceryStore;
                delete outdoorRecSupplier;
                delete finalMap;

                //Setup game again
                //Set step limit for game until loss
                timeToDeath = 800;

                //Space locations setup - Outdoors (store fronts)
                outdoors = new Outdoors("Outside");

                //Space locations setup - Grocery store
                groceryStore = new GroceryStore("Grocery Store");

                //Space locations setup - Outdoor rec supplier
                outdoorRecSupplier = new OutdoorRecSupplier("Outdoor Recreational Supplier");

                //Space locations setup - Final map
                finalMap = new Field("Field");

                //Add doors to maps with map links
                addDoors();

                //Set current map to outdoors for start of game
                currentMap = outdoors;

                //Set player and location
                player = new Player("player", currentMap->getStartRow(), currentMap->getStartCol());

                //Set player in map
                currentMap->setPlayerLocation(player, player->getRows(), player->getCols());
            }
        }

        //User elected to quit game at start, no need to reset game
        else {
            resetGame = false;
        }

    } while (resetGame);

}

//Controller to allow for user selection for player movement on board. Prompts user for input
//of direction to move and moves player piece in that direction. Returns boolean value for
//exit game. True to exit, false to keep playing.
bool Game::movePlayer() {
    bool playGame = true;
    //Player performed an action of some sort successfully
    bool playerEngaged = false;

    do {
        //Display control options for user
        controlsDisplay();

        std::string moveSelection = "";
        //Accept and validate input from user for movement selection
        moveSelection = validateMove();

        //Move up on map
        if (moveSelection == "W") {
            //Check to see if a map change is needed if moving from open door space, out of current map bounds.
            if ((currentMap->getCurrentSpace()->getName() == "open door" || currentMap->getCurrentSpace()->getName()
                == "open space") && player->getUp()->getMapName() != "") {
                changeMaps(player->getUp());
            }

            //If move location is not null, then check to make sure object can be passed through/over and move if so
            else if (!player->getUp()->getSolid()) {
                //Remove old player position from map to move to next position
                currentMap->removePlayer(player);

                //Adjust player character position
                player->setRows((player->getRows() - 1));

                playerEngaged = true;
            }
            //Player cannot move there, output message as to why
            else {
                std::cout << "Player could not be moved to that location, there is a " <<
                          player->getUp()->getName() << " there!" << std::endl << std::endl;
            }
        }

        //Move down on map
        else if (moveSelection == "S") {
            //Check to see if a map change is needed if moving from open door space, out of current map bounds.
            if ((currentMap->getCurrentSpace()->getName() == "open door" || currentMap->getCurrentSpace()->getName()
                == "open space") && player->getDown()->getMapName() != "") {
                changeMaps(player->getDown());
            }

            //If move location is not null, then check to make sure object can be passed through/over and move if so
            else if (!player->getDown()->getSolid()) {
                //Remove old player position from map to move to next position
                currentMap->removePlayer(player);

                //Adjust player character position
                player->setRows((player->getRows() + 1));

                playerEngaged = true;
            }
            //Player cannot move there, output message as to why
            else {
                std::cout << "Player could not be moved to that location, there is a " <<
                          player->getDown()->getName() << " there!" << std::endl << std::endl;
            }
        }

        //Move left on map
        else if (moveSelection == "A") {
            //Check to see if a map change is needed if moving from open door space, out of current map bounds.
            if ((currentMap->getCurrentSpace()->getName() == "open door" || currentMap->getCurrentSpace()->getName()
                == "open space") && player->getLeft()->getMapName() != "") {
                changeMaps(player->getLeft());
            }

            //If move location is not null, then check to make sure object can be passed through/over and move if so
            else if (!player->getLeft()->getSolid()) {
                //Remove old player position from map to move to next position
                currentMap->removePlayer(player);

                //Adjust player character position
                player->setCols((player->getCols() - 1));

                playerEngaged = true;
            }

            //Player cannot move there, output message as to why
            else {
                std::cout << "Player could not be moved to that location, there is a " <<
                          player->getLeft()->getName() << " there!" << std::endl << std::endl;
            }
        }

        //Move right on map
        else if (moveSelection == "D") {
            //Check to see if a map change is needed if moving from open door space, out of current map bounds.
            if ((currentMap->getCurrentSpace()->getName() == "open door" || currentMap->getCurrentSpace()->getName()
                == "open space") && player->getRight()->getMapName() != "") {
                changeMaps(player->getRight());
            }

            //If move location is not null, then check to make sure object can be passed through/over and move if so
            else if (!player->getRight()->getSolid()) {
                //Remove old player position from map to move to next position
                currentMap->removePlayer(player);

                //Adjust player character position
                player->setCols((player->getCols() + 1));

                playerEngaged = true;
            }
            //Player cannot move there, output message as to why
            else {
                std::cout << "Player could not be moved to that location, there is a " <<
                    player->getRight()->getName() << " there!" << std::endl << std::endl;
            }
        }

        //Interact with Space object (up, down, left, or right of players current position)
        else if (moveSelection == "E") {
            //Interact with Space object. Request user input for which direction to interact with
            //and interact with that object.
            interactObject();

            playerEngaged = true;
        }

        else if (moveSelection == "I") {
            player->viewInventory();
        }

        //Exit game
        else if (moveSelection == "Q") {
            playGame = false;
        }

        if (moveSelection != "E" && moveSelection != "I" && playerEngaged && moveSelection != "Q") {
            //Move player to new space
            currentMap->setPlayerLocation(player, player->getRows(), player->getCols());
        }

        //If player could not be moved and user did not elect to exit game, inform user that wall was hit.
        if (!playerEngaged && playGame) {
            //Display map again
            currentMap->drawMap();
        }

    } while (!playerEngaged && playGame);

    return playGame;
}

//Output game controls to terminal for user viewing
void Game::controlsDisplay() {
    //Output turns left in game
    std::cout << "Time Left: " << timeToDeath << std::endl << std::endl;

    //Output controls
    std::cout << "GAME MOVEMENT: You may use capitalized or lower-case letter." << std::endl;
    std::cout << "W/w = Move up         S/s = Move down" << std::endl;
    std::cout << "A/a = Move left       D/d = Move right" << std::endl;
    std::cout << "I/i = View inventory bag" << std::endl;
    std::cout << "E/e = Interact with object" << std::endl;
    std::cout << "Q/q = Exit game" << std::endl;

}



//If player elects to engage with a Space object, function is called to interact with object. Function outputs
//and accepts/validates direction of object to interact with and performs interaction with object.
void Game::interactObject() {
    int menuSelection = 0;

    std::cout << "Which direction would you like to interact with? Please select from the integer\n" <<
        "options below." << std::endl;

    std::cout << "1. Up         2. Down\n3. Left       4. Right" << std::endl;

    //Accept/validate integer input from user. Re-prompt if necessary.
    menuSelection = validateInputRangeInt(1, 4);

    std::string objectName = "";

    //If menu selection was for up, attempt to interact with Space object above player
    if (menuSelection == 1) {

        //Interact with object
        player->interactObject(player->getUp());

        std::cout << std::endl;

        //Check if interaction from player is on an item object, if so item is picked up and is removed from map
        if (player->getUp()->getIsItem()) {

            //If the item is set to true for picked up, remove item from board
            if (dynamic_cast<GamePiece*>(player->getUp())->getPickedUp()) {
                //Remove object that is picked up from map
                currentMap->removeObject(player->getUp());
            }
        }
    }

    //If menu selection was for down, attempt to interact with Space object above player
    if (menuSelection == 2) {
        //Interact with object
        player->interactObject(player->getDown());

        std::cout << std::endl;

        //Check if interaction from player is on an item object, if so item is picked up and is removed from map
        if (player->getDown()->getIsItem()) {
            //If the item is set to true for picked up, remove item from board
            if (dynamic_cast<GamePiece*>(player->getDown())->getPickedUp()) {
                //Remove object that is picked up from map
                currentMap->removeObject(player->getDown());
            }
        }
    }

    //If menu selection was for left, attempt to interact with Space object above player
    if (menuSelection == 3) {
        //Interact with object
        player->interactObject(player->getLeft());

        std::cout << std::endl;

        //Check if interaction from player is on an item object, if so item is picked up and is removed from map
        if (player->getLeft()->getIsItem()) {
            //If the item is set to true for picked up, remove item from board
            if (dynamic_cast<GamePiece*>(player->getLeft())->getPickedUp()) {
                //Remove object that is picked up from map
                currentMap->removeObject(player->getLeft());
            }
        }
    }

    //If menu selection was for right, attempt to interact with Space object above player
    if (menuSelection == 4) {
        //Interact with object
        player->interactObject(player->getRight());

        std::cout << std::endl;

        //Check if interaction from player is on an item object, if so item is picked up and is removed from map
        if (player->getRight()->getIsItem()) {
            //If the item is set to true for picked up, remove item from board
            if (dynamic_cast<GamePiece*>(player->getRight())->getPickedUp()) {
                //Remove object that is picked up from map
                currentMap->removeObject(player->getRight());
            }
        }
    }
}

//If moving through door linked to another map, change map location of player as movement and set player in the new map
//location. Takes Space pointer as parameter.
void Game::changeMaps(Space* inputMoveSpace) {
        //Remove player from current map
        currentMap->removePlayer(player);

        //If player moves to grocery store, change map to grocery and output map description
        if (inputMoveSpace->getMapName() == "grocery store") {
            //Output map description
            groceryStoreDesc();
            std::cout << std::endl;

            //Change map
            currentMap = groceryStore;
        }

        //If player moves through door to outdoors, change map to outdoors
        else if (inputMoveSpace->getMapName() == "outdoors") {
            //Output map description
            outdoorDesc();
            std::cout << std::endl;

            //Change map
            currentMap = outdoors;
        }

        //If player moves through door to outdoor rec supplier, change map to rec supplier
        else if (inputMoveSpace->getMapName() == "outdoor rec supplier") {
            //Output map description
            recSupplierDesc();
            std::cout << std::endl;

            //Change map
            currentMap = outdoorRecSupplier;
        }

        //If player moves through door to field from outdoors, change map to field
        else if (inputMoveSpace->getMapName() == "field") {
            //Output map description
            finalFieldDesc();
            std::cout << std::endl;

            //Change map
            currentMap = finalMap;
        }

        //Adjust player character position
        player->setRows(inputMoveSpace->getRows());
        player->setCols(inputMoveSpace->getCols());

        //Place player on new map with starting position after moving through door
        currentMap->setPlayerLocation(player, player->getRows(), player->getCols());

        //If the door starts out closed, set door on other side to open
        if (currentMap->getCurrentSpace()->getName() == "closed door") {
            //Set door to open on new map
            currentMap->getCurrentSpace()->setVisual('/');
            currentMap->getCurrentSpace()->setSolid(false);
            currentMap->getCurrentSpace()->setName("open door");
        }
}


//Add/link doors between maps on game to allow for traversal between maps within the world.
void Game::addDoors() {
    //Create door spaces to add to maps
    Space* outsideGroceryDoor = new Door("outdoors", 15, 0);
    Space* groceryOutsideDoor = new Door("grocery store", 9, 34);
    Space* outsideRecSupplier = new Door("outdoors", 4, 0);
    Space* recSupplierOutside = new Door("outdoor rec supplier", 4, 11);
    Space* outsideField = new Door("outdoors", 19, 9);
    Space* fieldOutside = new Door("field", 0, 9);

    //Change visuals of field/outside and set to open and not interactable - Open space entryway
    outsideField->setSolid(false);
    fieldOutside->setSolid(false);
    outsideField->setVisual('_');
    fieldOutside->setVisual('_');
    outsideField->setInteract(false);
    fieldOutside->setInteract(false);
    outsideField->setName("open space");
    fieldOutside->setName("open space");

    //Add door spaces to map
    //Doors between grocery and outside
    outdoors->addSpaceObject(outsideGroceryDoor, 15, 0);
    groceryStore->addSpaceObject(groceryOutsideDoor, 9, 34);

    //Doors between rec supplier and outside
    outdoors->addSpaceObject(outsideRecSupplier, 4, 0);
    outdoorRecSupplier->addSpaceObject(recSupplierOutside, 4, 11);

    //Space between outside and field
    outdoors->addSpaceObject(outsideField, 19, 9);
    finalMap->addSpaceObject(fieldOutside, 0, 9);


    //Set doors to link to other map location
    //Link doors between grocery and outside
    outsideGroceryDoor->setLeft(groceryOutsideDoor);
    groceryOutsideDoor->setRight(outsideGroceryDoor);

    //Link doors between rec supplier and outside
    outsideRecSupplier->setLeft(recSupplierOutside);
    recSupplierOutside->setRight(outsideRecSupplier);

    //Link doors between field and outside
    outsideField->setDown(fieldOutside);
    fieldOutside->setUp(outsideField);
}

//Allow user to select to start or exit game. Return boolean value for user selection.
bool Game::startMenu() {
    std::cout << "Would you like to play Zombie Survival - Days After? Please select an integer option below.\n" <<
                 "1. Yes\n" <<
                 "2. No" << std::endl;

    //Validate user input and re-prompt if necessary and store in int variable userSelection
    int userSelection = validateInputRangeInt(1, 2);

    bool startGame = false;
    //If user selected 1 for yes, set startGame to true.
    if (userSelection == 1) {
        startGame = true;
    }

    return startGame;
}

//Allow user to select reset game from scratch. Returns boolean value.
bool Game::resetMenu() {
    std::cout << "Would you like to reset the game to the beginning? Please select an integer option below.\n" <<
                 "1. Yes to reset\n" <<
                 "2. No to exit program" << std::endl;

    //Validate user input and re-prompt if necessary and store in int variable userSelection
    int userSelection = validateInputRangeInt(1, 2);

    bool resetGame = false;
    //If user selected 1 for yes, set startGame to true.
    if (userSelection == 1) {
        resetGame = true;
    }

    return resetGame;
}

//Output game description to player at start of the game
void Game::gameDesc() {
    std::cout << "THE DAYS AFTER - ZOMBIE SURVIVAL GAME\n" <<
                 "Zombies have been roaming the earth for years as small colonies of people are\n" <<
                 "scattered across the land in hiding for survival. A disease has begun to spread\n" <<
                 "among the people in your encampment and you were dispatched to find medicine.\n" <<
                 "Just beware of zombies as you look for the things you need to save your people.\n" <<
                 "Upon finding the medicine, return to the door behind your starting point and \n" <<
                 "escape through the forest back to your colony." << std::endl;
}

//Output map description when entering outdoors map area
void Game::outdoorDesc() {
    std::cout << "It is a crisp fall day with a light sprinkle on your face as you wander into town.\n" <<
                 "You see two shops to your left as you enter town. The first on the left appears to\n" <<
                 "be a small grocery store, followed by an outdoors recreational supplier. Perhaps\n" <<
                 "you can find supplies within these shops." << std::endl;
}

//Output map description when entering grocery store map area
void Game::groceryStoreDesc() {
    std::cout << "You have entered a small grocery store. What a mess! Scattered shelves with a few\n" <<
                 "registers up front. Perhaps there is a pharmacy here that can help." << std::endl;
}

//Output map description when entering outdoor rec supplier area
void Game::recSupplierDesc() {
    std::cout << "You have entered a small recreational supplier. Although it appears most of the cases\n" <<
                 "have long since been cleaned out, perhaps you can find something to fight back with if \n" <<
                 "needed." << std::endl;
}

//Output map description when entering the final field map
void Game::finalFieldDesc() {
    std::cout << "You have entered a clearing with many visible zombies standing in your way. If you can only\n" <<
                 "just reach the end of the field to the clearing in the forest and you can sneak away. Just \n" <<
                 "make sure you have the medicine first!" << std::endl;
}