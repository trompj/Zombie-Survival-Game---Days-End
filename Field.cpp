/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Field class is a child class of Map. Field class represents the field map in game, which is used
 * as the final map location in the game.
 * Variables: Integer variables for rows/cols of map size and startingRow/startingColumn of player when placed on map
 * Functions: Constructor takes string for name of map and passes the four integer values to the Map class constructor
 * for map size and starting player location.
 * Field destructor destroys all zombies associated with zombies vector to free memory.
 * mapSetup - Sets up the Field map by adding zombies and objects/items needed in the map.
*/

#include "Field.hpp"

//Primary constructor for outdoor map area.
Field::Field(std::string inputName) : Map(inputName, rows, cols, startingRow, startingCol) {
    mapSetup();
}

//Destructor to delete allocated memory involved with zombie placements on map
Field::~Field() {
    for (unsigned count = 0; count < zombies.size(); count++) {
        delete zombies[count]->getCurrentSpace();
    }
}

//Set up outdoors map - Add in all items and additional environmental map details as necessary
void Field::mapSetup() {
    //Add zombies to vector container
    zombies.push_back(new Zombie("zombie", 3, 5));
    zombies.push_back(new Zombie("zombie", 6, 11));
    zombies.push_back(new Zombie("zombie", 12, 13));
    zombies.push_back(new Zombie("zombie", 8, 9));

    //Add zombies to map
    setZombieLocation(zombies[0]);
    setZombieLocation(zombies[1]);
    setZombieLocation(zombies[2]);
    setZombieLocation(zombies[3]);

    //Add exit point to map
    addSpaceObject(new ExitPoint(18, 7), 18, 7);
}