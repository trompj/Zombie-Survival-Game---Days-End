/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: GroceryStore class is a child class of Map. GroceryStore class represents the grocery/convenience store
 * map in game, which is used as the map location of the pharmacy and locked up medication required for game win.
 * Variables: Integer variables for rows/cols of map size and startingRow/startingColumn (if needed for map) of player
 * when placed on map.
 * Functions: Constructor takes string for name of map and passes the four integer values to the Map class constructor
 * for map size and starting player location. Calls mapSetup to setup map objects.
 * Field destructor destroys all zombies associated with zombies vector to free memory.
 * mapSetup - Sets up the grocery store map by adding zombies and objects/items needed in the map.
*/

#include "GroceryStore.hpp"

//Primary constructor for grocery store map area - Constructor takes string for name of map and passes the four
//integer values to the Map class constructor for map size and starting player location. Calls mapSetup.
GroceryStore::GroceryStore(std::string inputName) : Map(inputName, rows, cols, startingRow, startingCol) {
    mapSetup();
}


//Destructor for grocery store map
GroceryStore::~GroceryStore() {
    for (unsigned count = 0; count < zombies.size(); count++) {
        delete zombies[count]->getCurrentSpace();
    }
}

//Set up grocery store map - Add in all doors/items as necessary and adds zombies/objects/items needed in map.
//Such as medication for game win.
void GroceryStore::mapSetup() {
    //Add wall-like features such as shelves and counters
    //Add column 6 shelves
    for (int row = 2; row < rows; row++) {
        if (row != 6 && row < 11) {
            Space* newWall = new Wall();

            newWall->setName("shelf");

            addSpaceObject(newWall, row, 6);
        }
    }

    //Add column 12 shelves
    for (int row = 2; row < rows; row++) {
        if (row != 6 && row < 11) {
            Space* newWall = new Wall();

            newWall->setName("shelf");

            addSpaceObject(newWall, row, 12);
        }
    }

    //Add column 18 shelves
    for (int row = 2; row < rows; row++) {
        if (row != 6 && row < 11) {
            Space* newWall = new Wall();

            newWall->setName("shelf");

            addSpaceObject(newWall, row, 18);
        }
    }

    //add column 24 shelves
    for (int row = 2; row < rows; row++) {
        if (row != 6 && row < 11) {
            Space* newWall = new Wall();

            newWall->setName("shelf");

            addSpaceObject(newWall, row, 24);
        }
    }

    //Add additional wall units to make one wall into a locked "pharmacy" to hold medication
    addSpaceObject(new Wall(), 5, 5);
    addSpaceObject(new Wall(), 5, 4);
    addSpaceObject(new Wall(), 5, 3);
    addSpaceObject(new Wall(), 5, 2);
    addSpaceObject(new Wall(), 5, 1);

    //Add locked door to "pharmacy"
    Space* lockedDoor = new Door("grocery store", 1, 6);
    dynamic_cast<Door*>(lockedDoor)->setName("locked door");
    dynamic_cast<Door*>(lockedDoor)->setLocked(true);
    addSpaceObject(lockedDoor, 1, 6);


    //Add register counters (col 30/31)
    addSpaceObject(new Wall(), 3, 30);
    addSpaceObject(new Wall(), 3, 31);
    addSpaceObject(new Wall(), 5, 30);
    addSpaceObject(new Wall(), 5, 31);
    addSpaceObject(new Wall(), 7, 30);
    addSpaceObject(new Wall(), 7, 31);


    //Add items to map
    addSpaceObject(new Medicine(3, 5), 3, 5);

    //Add zombies to vector container
    zombies.push_back(new Zombie("zombie", 1, 15));
    zombies.push_back(new Zombie("zombie", 9, 10));
    zombies.push_back(new Zombie("zombie", 8, 3));

    //Add zombies to map
    setZombieLocation(zombies[0]);
    setZombieLocation(zombies[1]);
    setZombieLocation(zombies[2]);
}

