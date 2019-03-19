/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Outdoors class is a child class of Map. This class represents the starting point of the map, indicating
 * that the user just got into town in search of medication. Class contains key item and doors to all other maps in game.
 * The key is used to open the pharmacy door in the grocery store map.
 * Variables: Integer variables for rows/cols of map size and startingRow/startingColumn of player when placed on map.
 * Functions: Constructor takes string for name of map and passes the four integer values to the Map class constructor
 * for map size and starting player location.
 * Outdoors destructor destroys all zombies associated with zombies vector to free memory.
 * mapSetup - Sets up the Outdoors map by adding zombies and objects/items needed in the map such as key.
*/

#include "Outdoors.hpp"

//Primary constructor for outdoor map area - takes string for name of map and passes the four integer values to the
//Map class constructor for map size and starting player location.
Outdoors::Outdoors(std::string inputName) : Map(inputName, rows, cols, startingRow, startingCol) {
    mapSetup();
}

//Destructor to delete allocated memory involved with zombie placements on map
Outdoors::~Outdoors() {
    for (unsigned count = 0; count < zombies.size(); count++) {
        delete zombies[count]->getCurrentSpace();
    }
}

//Set up outdoors map - Add in all items and additional environmental map details as necessary such as zombies
//and the key.
void Outdoors::mapSetup() {
    //Add key item to map for vehicle
    addSpaceObject(new Key(1, 17), 1, 17);

    //Add zombies to vector container
    zombies.push_back(new Zombie("zombie", 3, 5));
    zombies.push_back(new Zombie("zombie", 6, 11));
    zombies.push_back(new Zombie("zombie", 12, 13));

    //Add zombies to map
    setZombieLocation(zombies[0]);
    setZombieLocation(zombies[1]);
    setZombieLocation(zombies[2]);
}
