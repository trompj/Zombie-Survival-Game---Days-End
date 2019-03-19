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

#ifndef FIELD_HPP
#define FIELD_HPP


#include "Map.hpp"
#include "Space.hpp"
#include "Door.hpp"
#include "Zombie.hpp"
#include "ExitPoint.hpp"

class Field : public Map {
private:
    static const int rows = 20,
                     cols = 20,
                     startingRow = 18,
                     startingCol = 9;

public:
    //Primary constructor for final outdoor map area. Takes string value for name of map being created.
    Field(std::string);

    //Destructor to delete allocated memory involved with zombie placements on map
    ~Field();

    //Set up final outdoors map - Add in all items and additional environmental map details as necessary
    void mapSetup();

};


#endif //FIELD_HPP
