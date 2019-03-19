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

#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include "Space.hpp"
#include "Wall.hpp"
#include "Player.hpp"
#include "Floor.hpp"
#include "Zombie.hpp"
#include "Door.hpp"

class Map {
protected:
    //Name of map
    std::string mapName;

    //Spaces/tiles in map
    Space*** mapTiles;

    //Player occupied Space pointer
    Space* playerOccupiedSpace;

    //Size of map
    int rows,
        cols;

    //Map player starting location
    int startRow,
        startCol;

    //Zombies placed on map held in vector container
    std::vector <Zombie*> zombies;

    //Initialize map according to size and layout provided as filled with floor spaces that are surrounded by walls.
    //Pointers for each space are assigned through setSpacePtrs.
    void initializeMap();

    //Set directional space pointers for each space. Takes Space** as the space to set pointers for and the row/col
    //location of that space as parameters. Sets all surrounding spaces to point to space passed to function.
    void setSpacePtrs(Space**, int, int);

public:
    //Declare map size and name and player starting location for map declaration. Sets up initial details for all maps.
    //Takes string value for name of map and int values for row/col of map size and row/col of starting location of player
    //if player is initially started in that map at start of game. Sets pointers to nullptr and calls initializeMap to
    //create outline of map with walls and floor spaces.
    Map(std::string, int, int, int, int);

    //Destructor frees all dynamically allocated memory of Map class that is currently within the mapTiles array at end
    //of game, as well ass the playerOccupiedSpace pointer. Zombies are deleted in child classes.
    virtual ~Map();

    //Output visualization of map by character representations of all Space objects
    void drawMap();

    //Remove zombie passed as parameter to function from board. Does not delete zombie, but removes from map.
    void removeZombie(Zombie*);

    //Set zombie passed as parameter on board for visualization.
    void setZombieLocation(Zombie*&);

    //Remove player from board and replace space that player was on with previous space.
    void removePlayer(Player*);

    //Set player on board and save location that player is moving to in a temporary holder. Takes Player pointer address
    //as parameter and two int values indicating row/col that player is about to move to.
    void setPlayerLocation(Player*&, int, int);

    //Add Space type to location on map and link surrounding pointers. Takes Space object pointer and
    //int values for location of object in map space as parameters. Calls setSpacePtrs to set surrounding
    //objects to point to Space being added.
    void addSpaceObject(Space* inputSpace, int inputRow, int inputCol);

    //Return integer value for starting row for player object
    int getStartRow();

    //Return integer value for starting column for player object
    int getStartCol();

    //Return Space pointer for current player occupied space
    Space* getCurrentSpace();

    //Default map setup function for abstract virtual function (no action) - Child class map types set up map using
    //overridden function.
    virtual void mapSetup() = 0;

    //Remove/replace item object in map after pick up with floor space. Takes Space pointer for object being removed.
    void removeObject(Space*);

    //Move zombies around map. Activate zombie movement function for each zombie on map while looping through vector.
    //Zombies are removed from map, new locations are determined through Zombie class, and zombies are moved. If zombie
    //attacks player but player has a knife, zombie dies and is removed from game.
    void moveZombies();

    //Check surroundings around player for zombie. If zombie is present, player is attacked. Player pointer is passed as
    //parameter to check around up, down, left, right spaces from player.
    void checkZombies(Player* inputPlayer);
};

#endif //MAP_HPP
