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

#ifndef OUTDOORRECSUPPLIER_HPP
#define OUTDOORRECSUPPLIER_HPP

#include "Map.hpp"
#include "Door.hpp"
#include "Knife.hpp"

class OutdoorRecSupplier : public Map {
private:
    static const int rows = 7,
            cols = 12,
            startingRow = 4,
            startingCol = 11;
public:
    //Primary constructor for rec supplier map area - takes string for name of map and passes the four integer
    //values to the Map class constructor for map size and starting player location.
    OutdoorRecSupplier(std::string);

    //Destructor for rec supplier map frees all memory allocated to zombies in map.
    ~OutdoorRecSupplier();

    //Set up grocery store map - Add in all doors/items as necessary such as zombies and knives.
    void mapSetup();

};


#endif //OUTDOORRECSUPPLIER_HPP
