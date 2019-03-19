/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Game class combines all elements of the game into one functional program. Creates all menu outputs and
 * contains all map/player pointer objects. Game class runs a zombie survival game in which player must find objects
 * and avoid getting killed by zombies in the process to save his colony.
 * Variables: timeToDeath: Step counter until the end of the game when player loses if objectives are still not met.
 * currentMap: Map pointer to the map that player is currently in.
 * outdoors: Map pointer to outdoors level.
 * groceryStore: Map pointer to groceryStore level.
 * outdoorRecSupplier: Map pointer to the outdoor rec supplier map.
 * finalMap: Map pointer to the final map location (Field)
 * player: Player pointer to the player object in game.
 * Functions: Constructor sets up Game object by setting timeToDeath, allocating space for all maps, setting currentMap to outdoors,
 * allocating space to player, place player on currentMap, and call addDoors function to manually add linked doors
 * between maps.
 * Destructor deletes all instances of Map that was dynamically allocated.
 * runGame - Primary controller for game, runs all menu options and combines functionality. If user starts playing game,
 * menu prints allowing user to reset game when either user elects to quit or game ends due to loss or win.
 * movePlayer - Controller to allow for user selection for player movement on board. Prompts user for input of
 * direction to move and moves player piece in that direction. Returns boolean value for exit game. True to exit,
 * false to keep playing.
 * controlsDisplay - Output game controls to terminal for user viewing.
 * interactObject - If player elects to engage with a Space object, function is called to interact with object.
 * Function outputs and accepts/validates direction of object to interact with and performs interaction with object.
 * changeMaps - If moving through door linked to another map, change map location of player as movement and set player
 * in the new map location. Takes Space pointer as parameter.
 * addDoors - Add/link doors between maps on game to allow for traversal between maps within the world.
 * startMenu - Allow user to select to start or exit game. Return boolean value for user selection.
 * gameDesc - Outputs information/introduction of game and its premise.
 * outdoorDesc - Describes the outdoor map each time the map is changed to outdoors.
 * groceryStoreDesc - Describes the grocery store map each time the map is changed to grocery store.
 * recSupplierDesc - Describes the recreational supplier map each time the map is changed to rec supplier.
 * finalFieldDesc - Describes the final field map, each time the final map is entered.
 * resetMenu - Allow user to select reset game from scratch. Returns boolean value for user selection.
*/

#ifndef GAME_HPP
#define GAME_HPP

#include "Player.hpp"
#include "Map.hpp"
#include "Outdoors.hpp"
#include "GroceryStore.hpp"
#include "OutdoorRecSupplier.hpp"
#include "inputValidation.hpp"
#include "Field.hpp"
#include "Door.hpp"

class Game {
private:
    //Units until it is too late, game is lost and characters die
    int timeToDeath = 800;

    //Current map that player is located in
    Map* currentMap;

    //different maps/rooms used throughout game
    Map* outdoors;
    Map* groceryStore;
    Map* outdoorRecSupplier;
    Map* finalMap;

    //Player variable pointer
    Player* player;


    //Output game description to player at start of the game
    void gameDesc();

    //Output map description when entering outdoors map area
    void outdoorDesc();

    //Output map description when entering grocery store map area
    void groceryStoreDesc();

    //Output map description when entering outdoor rec supplier area
    void recSupplierDesc();

    //Output map description when entering the final field map
    void finalFieldDesc();

    //Controller to allow for user selection for player movement on board. Prompts user for input
    //of direction to move and moves player piece in that direction. Returns boolean value for
    //exit game. True to exit, false to keep playing.
    bool movePlayer();

    //Output game controls to terminal for user viewing
    void controlsDisplay();

    //If player elects to engage with a Space object, function is called to interact with object. Function outputs
    //and accepts/validates direction of object to interact with and performs interaction with object.
    void interactObject();

    //If moving through door linked to another map, change map location of player as movement and set player in the new map
    //location. Takes Space pointer as parameter.
    void changeMaps(Space*);

    //Add/link doors between maps on game to allow for traversal between maps within the world.
    void addDoors();

public:
    //Sets up Game object by setting timeToDeath, allocating space for all maps, setting currentMap to outdoors,
    //allocating space to player, place player on currentMap, and call addDoors function to manually add linked doors
    //between maps.
    Game();

    //Free all dynamically allocated memory - deletes all instances of Map that was dynamically allocated.
    ~Game();

    //Primary controller for game, runs all menu options and combines functionality. Returns boolean value fo true while
    //game is running, allowing for loop of gameplay while resetting game.
    void runGame();

    //Allow user to select to start or exit game. Return boolean value for user selection.
    bool startMenu();

    //Allow user to select reset game from scratch. Returns boolean value for user selection.
    bool resetMenu();
};


#endif //GAME_HPP
