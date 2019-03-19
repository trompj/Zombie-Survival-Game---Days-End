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

#ifndef GROCERYSTORE_HPP
#define GROCERYSTORE_HPP

#include "Map.hpp"
#include "Door.hpp"
#include "Medicine.hpp"

class GroceryStore : public Map {
private:
    static const int rows = 13,
                     cols = 35,
                     startingRow = 9,
                     startingCol = 34;
public:
    //Primary constructor for grocery store map area - Constructor takes string for name of map and passes the four
    //integer values to the Map class constructor for map size and starting player location. Calls mapSetup.
    GroceryStore(std::string);

    //Destructor for grocery store map to free allocated memory
    ~GroceryStore();

    //Set up grocery store map - Add in all doors/items as necessary and adds zombies/objects/items needed in map.
    //Such as medication for game win.
    void mapSetup();
};


#endif //GROCERYSTORE_HPP
