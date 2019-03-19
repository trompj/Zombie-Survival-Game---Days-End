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

#ifndef OUTDOORS_HPP
#define OUTDOORS_HPP

#include "Map.hpp"
#include "Space.hpp"
#include "Door.hpp"
#include "Key.hpp"
#include "Zombie.hpp"

class Outdoors : public Map {
private:
    static const int rows = 20,
                     cols = 20,
                     startingRow = 18,
                     startingCol = 9;



public:
    //Primary constructor for outdoor map area - takes string for name of map and passes the four integer values to the
    //Map class constructor for map size and starting player location.
    Outdoors(std::string);

    //Destructor to delete allocated memory involved with zombie placements on map
    ~Outdoors();

    //Set up outdoors map - Add in all items and additional environmental map details as necessary such as zombies
    //and the key.
    void mapSetup();

};


#endif //OUTDOORS_HPP
