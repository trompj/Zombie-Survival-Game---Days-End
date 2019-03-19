/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: OutdoorRecSupplier class is a child class of Map. This class represents the rec supplier map in game,
 * which is used as an optional objective for the user. The player may pick up 1 or 2 knives in this shop which can
 * each be used to kill a zombie if encountered. Each knife is only worth one kill in a defensive capacity.
 * Variables: Integer variables for rows/cols of map size and startingRow/startingColumn of player when placed on map.
 * Functions: Constructor takes string for name of map and passes the four integer values to the Map class constructor
 * for map size and starting player location.
 * OutdoorRecSupplier destructor destroys all zombies associated with zombies vector to free memory.
 * mapSetup - Sets up the OutdoorRecSupplier map by adding zombies and objects/items needed in the map.
*/

#include "OutdoorRecSupplier.hpp"

//Primary constructor for rec supplier map area - takes string for name of map and passes the four integer
//values to the Map class constructor for map size and starting player location.
OutdoorRecSupplier::OutdoorRecSupplier(std::string inputName) : Map(inputName, rows, cols, startingRow, startingCol) {
    mapSetup();
}

//Destructor for rec supplier map frees all memory allocated to zombies in map.
OutdoorRecSupplier::~OutdoorRecSupplier() {
    for (unsigned count = 0; count < zombies.size(); count++) {
        delete zombies[count]->getCurrentSpace();
    }
}

//Set up grocery store map - Add in all doors/items as necessary such as zombies and knives
void OutdoorRecSupplier::mapSetup() {
    //Add wall-like features such as shelves and counters
    //Add display case along walls with item(s) and place door in front
    addSpaceObject(new Wall(), 2, 1);
    addSpaceObject(new Wall(), 2, 2);
    addSpaceObject(new Wall(), 4, 1);
    addSpaceObject(new Wall(), 4, 2);
    addSpaceObject(new Door("outdoor rec supplier", 1, 2), 1, 2);
    addSpaceObject(new Door("outdoor rec supplier", 3, 2), 3, 2);
    addSpaceObject(new Door("outdoor rec supplier", 5, 2), 5, 2);

    //Add item(s) to map (weapons in outdoor rec supplier)
    addSpaceObject(new Knife(1, 1), 1, 1);
    addSpaceObject(new Knife(5, 1), 5, 1);

    //Add zombies to vector container
    zombies.push_back(new Zombie("zombie", 5, 5));

    //Add zombies to map
    setZombieLocation(zombies[0]);
}