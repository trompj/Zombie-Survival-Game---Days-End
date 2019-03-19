/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Map class is the abstract parent class of all Map types in game such as outdoors, field, etc... Class
 * sets up the basic framework of all maps and fine details (anything within walls) are initiated by child classes.
 * Doors leading between maps are created and initialized by Game class.
 * Variables: Integer variables for rows/cols of map size and startingRow/startingColumn of player when placed on map
 * Functions: Declare map size and name and player starting location for map declaration. Sets up initial details for
 * all maps. Takes string value for name of map and int values for row/col of map size and row/col of starting location
 * of player if player is initially started in that map at start of game. Sets pointers to nullptr and calls
 * initializeMap to create outline of map with walls and floor spaces.
 * Destructor frees all dynamically allocated memory of Map class that is currently within the mapTiles array at end of
 * game, as well ass the playerOccupiedSpace pointer. Zombies are deleted in child classes.
 * initializeMap - Initialize map according to size and layout provided as filled with floor spaces that are surrounded
 * by walls. Pointers for each space are assigned through setSpacePtrs.
 * setSpacePtrs - Set directional space pointers for each space. Takes Space** as the space to set pointers for and the
 * row/col location of that space as parameters. Sets all surrounding spaces to point to space passed to function.
 * drawMap - Output visualization of map by character representations of all Space objects
 * removeZombie - Remove zombie passed as parameter to function from board. Does not delete zombie, but removes from map.
 * setZombieLocation - Set zombie passed as parameter on board for visualization.
 * removePlayer - Remove player from board and replace space that player was on with previous space.
 * setPlayerLocation - Set player on board and save location that player is moving to in a temporary holder. Takes
 * Player pointer address as parameter and two int values indicating row/col that player is about to move to.
 * addSpaceObject - Add Space type to location on map and link surrounding pointers. Takes Space object pointer and
 * int values for location of object in map space as parameters. Calls setSpacePtrs to set surrounding objects to point
 * to Space being added.
 * getStartRow - Return integer value for starting row for player object
 * getStartCol - Return integer value for starting col for player object
 * getCurrentSpace - Return Space pointer for current player occupied space
 * mapSetup - Default map setup function for abstract virtual function (no action) - Child class map types set up map
 * using overridden function.
 * removeObject - Remove/replace item object in map after pick up with Floor space. Takes Space pointer for object
 * being removed.
 * moveZombies - Move zombies around map. Activate zombie movement function for each zombie on map while looping through
 * vector. Zombies are removed from map, new locations are determined through Zombie class, and zombies are moved. If
 * zombie attacks player but player has a knife, zombie dies and is removed from game.
 * checkZombies - Check surroundings around player for zombie. If zombie is present, player is attacked. Player pointer
 * is passed as parameter to check around up, down, left, right spaces from player.
*/

#include "Map.hpp"

//Declare map size and name and player starting location for map declaration. Sets up initial details for all maps.
//Takes string value for name of map and int values for row/col of map size and row/col of starting location of player
//if player is initially started in that map at start of game. Sets pointers to nullptr and calls initializeMap to
//create outline of map with walls and floor spaces.
Map::Map(std::string inputName, int inputRow, int inputCol, int startingRow, int startingCol) {
    //Set map name and size of map
    mapName = inputName;
    rows = inputRow;
    cols = inputCol;

    //Set starting row and column of map
    startRow = startingRow;
    startCol = startingCol;

    //Set map space pointer to null
    mapTiles = nullptr;

    //Set player occupied space to nullptr
    playerOccupiedSpace = nullptr;

    //Initialize map with basic walls and spaces
    initializeMap();
}

//Destructor frees all dynamically allocated memory of Map class that is currently within the mapTiles array at end
//of game, as well ass the playerOccupiedSpace pointer. Zombies are deleted in child classes.
Map::~Map() {
    //Free all memory allocated to individual tile spaces
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
                delete mapTiles[row][col];
        }

        //Delete second pointer for start of array
        delete[] mapTiles[row];
    }

    //Delete first pointer
    delete[] mapTiles;

    //Delete player space pointer
    delete playerOccupiedSpace;
}

//Initialize map according to size and layout provided as filled with floor spaces that are surrounded by walls.
//Pointers for each space are assigned through setSpacePtrs.
void Map::initializeMap() {
    //Set row size of map
    mapTiles = new Space**[rows];
    //Loop through rows of map creating new space pointers for columns
    for (int rowCount = 0; rowCount < rows; rowCount++) {
        mapTiles[rowCount] = new Space*[cols];
        for (int colCount = 0; colCount < cols; colCount++) {
            mapTiles[rowCount][colCount] = new Floor();
        }
    }

    //Create walls of map on top/bottom
    for (int count = 0; count < cols; count++) {
        //Set top row of walls and delete current allocation
        delete mapTiles[0][count];
        mapTiles[0][count] = new Wall();

        //Set bottom row of walls and delete current allocation
        delete mapTiles[rows-1][count];
        mapTiles[rows-1][count] = new Wall();
    }

    //Create walls of map on sides
    for (int count = 1; count < (rows-1); count++) {
        //Set left column walls and delete current allocation
        delete mapTiles[count][0];
        mapTiles[count][0] = new Wall();

        //Set right column walls and delete current allocation
        delete mapTiles[count][cols-1];
        mapTiles[count][cols-1] = new Wall();
    }

    //Once all spaces are added to map, assign pointer values to each Space
    for (int countRow = 0; countRow < rows; countRow++) {
        for (int countCol = 0; countCol < cols; countCol++) {
            setSpacePtrs(&mapTiles[countRow][countCol], countRow, countCol);
        }
    }

}

//Set directional space pointers for each space. Takes Space** as the space to set pointers for and the row/col
//location of that space as parameters. Sets all surrounding spaces to point to space passed to function.
void Map::setSpacePtrs(Space** inputSpace, int inputRow, int inputCol) {
    //Set Space pointer above added Space
    if (inputRow > 0) {
        mapTiles[inputRow-1][inputCol]->setDown(*inputSpace);
    }

    //Set Space pointer below added space
    if(inputRow < (rows-1)) {
        mapTiles[inputRow+1][inputCol]->setUp(*inputSpace);
    }


    //Set Space pointer left of added space
    if(inputCol > 0) {
        mapTiles[inputRow][inputCol-1]->setRight(*inputSpace);
    }

    //Set Space pointers right of added space
    if (inputCol < (cols-1)) {
        mapTiles[inputRow][inputCol+1]->setLeft(*inputSpace);
    }
}

//Output visualization of map by character representations of all Space objects
void Map::drawMap() {
    //Print 5 lines before map draw
    std::cout << std::endl;

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            //If space is not empty, print out visualization
            if (mapTiles[row][col] != nullptr) {
                std::cout << mapTiles[row][col]->getVisual();
            }
            //If nullptr/empty space, print empty space
            if (mapTiles[row][col] == nullptr) {
                std::cout << ' ';
            }
        }
        //End of column, move to next line
        std::cout << std::endl;
    }
}

//Remove zombie passed as parameter to function from board. Does not delete zombie, but removes from map.
void Map::removeZombie(Zombie* inputZombie) {
    Space* oldSpace = inputZombie->getCurrentSpace();

    //Set current zombie position to original Space value
    mapTiles[inputZombie->getRows()][inputZombie->getCols()] = inputZombie->getCurrentSpace();

    //Set space pointers around removed player back to original Space
    setSpacePtrs(&oldSpace, inputZombie->getRows(), inputZombie->getCols());

    //Set currentSpace in Zombie class to nullptr
    inputZombie->setCurrentSpace(nullptr);
}

//Set zombie passed as parameter on board for visualization.
void Map::setZombieLocation(Zombie*& inputZombie) {
    //Save space that player is about to occupy
    inputZombie->setCurrentSpace(mapTiles[inputZombie->getRows()][inputZombie->getCols()]);

    //Set zombie Space pointers for up, down, left, right to the same as space zombie is being moved onto
    inputZombie->setUp(inputZombie->getCurrentSpace()->getUp());
    inputZombie->setDown(inputZombie->getCurrentSpace()->getDown());
    inputZombie->setLeft(inputZombie->getCurrentSpace()->getLeft());
    inputZombie->setRight(inputZombie->getCurrentSpace()->getRight());

    //Place Zombie pointer onto map in new location
    mapTiles[inputZombie->getRows()][inputZombie->getCols()] = inputZombie;

    //Set space pointers around player to point to player
    setSpacePtrs(&mapTiles[inputZombie->getRows()][inputZombie->getCols()], inputZombie->getRows(),
            inputZombie->getCols());
}

//Remove player from board and replace space that player was on with previous space.
void Map::removePlayer(Player* inputPlayer) {
    mapTiles[inputPlayer->getRows()][inputPlayer->getCols()] = playerOccupiedSpace;

    //Set space pointers around removed player back to original Space
    setSpacePtrs(&playerOccupiedSpace, inputPlayer->getRows(), inputPlayer->getCols());

    playerOccupiedSpace = nullptr;
}

//Set player on board and save location that player is moving to in a temporary holder. Takes Player pointer address
//as parameter and two int values indicating row/col that player is about to move to.
void Map::setPlayerLocation(Player*& inputPlayer, int inputRow, int inputCol) {
    //Save space that player is about to occupy
    playerOccupiedSpace = mapTiles[inputRow][inputCol];

    //Set player Space pointers for up, down, left, right to space player is being moved onto
    inputPlayer->setUp(playerOccupiedSpace->getUp());
    inputPlayer->setDown(playerOccupiedSpace->getDown());
    inputPlayer->setLeft(playerOccupiedSpace->getLeft());
    inputPlayer->setRight(playerOccupiedSpace->getRight());

    //Place Player pointer onto map in new location
    mapTiles[inputRow][inputCol] = inputPlayer;

    //Set space pointers around player to point to player
    setSpacePtrs(&mapTiles[inputRow][inputCol], inputRow, inputCol);
}

//Add Space type to location on map and link surrounding pointers. Takes Space object pointer and
//int values for location of object in map space as parameters. Calls setSpacePtrs to set surrounding
//objects to point to Space being added.
void Map::addSpaceObject(Space* inputSpaceObj, int inputRow, int inputCol) {
    //Set input space object pointers to pointer values of object being replaced
    inputSpaceObj->setUp(mapTiles[inputRow][inputCol]->getUp());
    inputSpaceObj->setDown(mapTiles[inputRow][inputCol]->getDown());
    inputSpaceObj->setLeft(mapTiles[inputRow][inputCol]->getLeft());
    inputSpaceObj->setRight(mapTiles[inputRow][inputCol]->getRight());

    //Remove previous space type
    delete mapTiles[inputRow][inputCol];
    //mapTiles[inputRow][inputCol] = nullptr;

    //Set row/col space to Space object passed to function.
    mapTiles[inputRow][inputCol] = inputSpaceObj;

    //Set pointers of surrounding Space objects to new Space object
    setSpacePtrs(&inputSpaceObj, inputRow, inputCol);
}

//Return integer value for starting row for player object
int Map::getStartRow() {
    return startRow;
}

//Return integer value for starting column for player object
int Map::getStartCol() {
    return startCol;
}

//Return Space pointer for current player occupied space
Space* Map::getCurrentSpace() {
    return playerOccupiedSpace;
}

//Default map setup function for abstract virtual function (no action) - Child class map types set up map using
//overridden function.
void Map::mapSetup() {}

//Remove/replace item object in map after pick up with floor space. Takes Space pointer for object being removed.
void Map::removeObject(Space* inputObject) {
    Space* newFloor = new Floor();

    //Set space that player is currently on to point to new floor object. If item is in direction of object being
    //removed, set playerOccupiedSpace to point to newFloor.
    //Check to left of player for item being removed
    if (playerOccupiedSpace->getLeft() == inputObject) {
        playerOccupiedSpace->setLeft(newFloor);
    }

    //Check to right of player for item being removed
    else if (playerOccupiedSpace->getRight() == inputObject) {
        playerOccupiedSpace->setRight(newFloor);
    }

    //Check above player for item being removed
    else if (playerOccupiedSpace->getUp() == inputObject) {
        playerOccupiedSpace->setUp(newFloor);
    }

    //Check below player for item being removed
    else if (playerOccupiedSpace->getDown() == inputObject) {
        playerOccupiedSpace->setDown(newFloor);
    }

    //Loop to check to make sure no zombies are next to item when it is picked up. If a zombie is next to item, must
    //set current space that zombie is on to point to new Floor space
    for (unsigned count = 0; count < zombies.size(); count++) {
        //Check to right of zombie for item being removed
        if (zombies[count]->getRight() == inputObject) {
            zombies[count]->getCurrentSpace()->setRight(newFloor);
        }

        //Check to left of zombie for item being removed
        else if (zombies[count]->getLeft() == inputObject) {
            zombies[count]->getCurrentSpace()->setLeft(newFloor);
        }

        //Check above zombie for item being removed
        else if (zombies[count]->getUp() == inputObject) {
            zombies[count]->getCurrentSpace()->setUp(newFloor);
        }

        //Check below zombie for item being removed
        else if (zombies[count]->getDown() == inputObject) {
            zombies[count]->getCurrentSpace()->setDown(newFloor);
        }
    }

    //Add new space for removed object (empty Floor) and remove object from board
    addSpaceObject(newFloor, inputObject->getRows(), inputObject->getCols());
}

//Move zombies around map. Activate zombie movement function for each zombie on map while looping through vector.
//Zombies are removed from map, new locations are determined through Zombie class, and zombies are moved. If zombie
//attacks player but player has a knife, zombie dies and is removed from game.
void Map::moveZombies() {
    //Find new movement location of each zombie on map. Loop through vector moving all zombies.
    //Move each zombie through removing zombie from board and placing in new location. Restore space that zombie is
    //currently occupied on and held in Zombie class and save new space to Zombie class before moving. Perform all
    //functions over loop of all zombies on map.
    for (unsigned count = 0; count < zombies.size(); count++) {
        //Remove zombie/restore space that zombie occupied
        removeZombie(zombies[count]);

        //Find new coordinates and movement of zombie based on move patterns in class and surroundings.
        zombies[count]->moveZombie();

        //If zombie is alive, set zombie on map in new location
        if (zombies[count]->getAlive()) {
            //Save space zombie is moving to and move zombie to new space on map
            setZombieLocation(zombies[count]);
        }
        //If zombie died, remove from vector and do not place on map.
        else {
            //Free memory for Zombie
            delete zombies[count];

            //Remove zombie object from vector
            zombies.erase(zombies.begin()+count);
        }
    }
}

//Check surroundings around player for zombie. If zombie is present, player is attacked. Player pointer is passed as
//parameter to check around up, down, left, right spaces from player.
void Map::checkZombies(Player* inputPlayer) {
    //Loop through zombies on map and check for Player in all lateral/vertical spaces (up/down/left/right)
    for (unsigned count = 0; count < zombies.size(); count++) {
        //If zombie is present and player has a knife, zombie is killed, otherwise player dies
        //Check up from zombie
        if (zombies[count]->getUp()->getName() == "player") {
            //If player has knife, zombie is killed
            if (inputPlayer->useItem("knife")) {
                std::cout << "Zombie attack was stopped with a knife to its head!"
                          << std::endl;

                //Remove zombie/restore space that zombie occupied
                removeZombie(zombies[count]);

                //Free memory for Zombie
                delete zombies[count];

                //Remove zombie object from vector
                zombies.erase(zombies.begin() + count);
            }
            //Player dies
            else {
                inputPlayer->setAlive(false);
            }
        }

        //Check down from zombie
        else if (zombies[count]->getDown()->getName() == "player") {
            //If player has knife, zombie is killed
            if (inputPlayer->useItem("knife")) {
                std::cout << "Zombie attack was stopped with a knife to its head!"
                          << std::endl;

                //Remove zombie/restore space that zombie occupied
                removeZombie(zombies[count]);

                //Free memory for Zombie
                delete zombies[count];

                //Remove zombie object from vector
                zombies.erase(zombies.begin() + count);
            }
            //Player dies
            else {
                inputPlayer->setAlive(false);
            }
        }

        //Check right of zombie
        else if (zombies[count]->getRight()->getName() == "player") {
            //If player has knife, zombie is killed
            if (inputPlayer->useItem("knife")) {
                std::cout << "Zombie attack was stopped with a knife to its head!"
                          << std::endl;

                //Remove zombie/restore space that zombie occupied
                removeZombie(zombies[count]);

                //Free memory for Zombie
                delete zombies[count];

                //Remove zombie object from vector
                zombies.erase(zombies.begin() + count);
            }
            //Player dies
            else {
                inputPlayer->setAlive(false);
            }
        }

        //Check left of zombie for player
        else if (zombies[count]->getLeft()->getName() == "player") {
            //If player has knife, zombie is killed
            if (inputPlayer->useItem("knife")) {
                std::cout << "Zombie attack was stopped with a knife to its head!"
                          << std::endl;

                //Remove zombie/restore space that zombie occupied
                removeZombie(zombies[count]);

                //Free memory for Zombie
                delete zombies[count];

                //Remove zombie object from vector
                zombies.erase(zombies.begin() + count);
            }
            //Player dies
            else {
                inputPlayer->setAlive(false);
            }
        }
    }
}