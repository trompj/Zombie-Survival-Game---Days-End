/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Player class is a child class of GamePiece, which is a child class of Space. Player class is used to
 * create a movable player object within the game world that can interact with objects, die, and possibly win the game.
 * Variables: static const char playerVisual for visualization of the player object on the map.
 * int value for maxInventory, which represents the maximum number of items Player class objects can hold.
 * Vector of strings representing inventory - A collection of items that player carries to complete objectives. There
 * are 4 items possible in game and each item is removed when used.
 * bool value for gameWin - set to false initially as game has not been won yet.
 * Functions: Constructor for player class to set up starting player attributes through GamePiece. Takes string input
 * for player name and two int values for row/col that player is placed in. Passes all values to GamePiece class as
 * well as player visualization. Within player constructor, player is set to alive and gameWin is set to false.
 * Default destructor - Removes all allocated memory as needed (nothing specific in player class)
 * addInventory - Add object to player inventory and return boolean value of true or false if object is picked up/added.
 * Takes string value of inventory item being added.
 * interactObject - Player object interaction - If interaction is available for object, perform interaction. This is
 * abstract virtual function for all Space type objects. Player class interactions initiate opening/closing doors and
 * picking up items. Also used in allowing user to open locked doors if they have a key. Takes Space pointer as
 * parameter for object being interacted with.
 * useItem - Search items in players item bag and return boolean value for whether or not item was in item bag.
 * If item is found, delete item and remove from bag.
 * setGameWin - Set game win value from boolean parameter passed to function.
 * getGameWin - Return game win boolean value.
 * viewInventory - Output inventory to screen for user viewing.
 * findItem - Search items in players item bag and return boolean value if it exists or not. Does not remove item from
 * bag like useItem
*/

#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <vector>
#include "GamePiece.hpp"
#include "Space.hpp"
#include "ExitPoint.hpp"
#include "inputValidation.hpp"

class Player : public GamePiece {
private:
    static const char playerVisual = '@';

    //Vector container for items in player bag
    std::vector <std::string> inventory;

    //Maximum inventory limit for player bag
    const int maxInventory = 3;

    //Boolean value for game objectives all achieved. Game win if set to true.
    bool gameWin = false;


public:
    //Constructor for player class to set up starting player attributes through GamePiece. Takes string input
    //for player name and two int values for row/col that player is placed in. Passes all values to GamePiece class as well
    //as player visualization. Within player constructor, player is set to alive and gameWin is set to false.
    Player(std::string, int, int);

    //Default destructor - Removes all allocated memory as needed
    ~Player();

    //Add object to player inventory and return boolean value of true or false if object is picked up/added. Takes string
    //value of inventory item being added.
    bool addInventory(std::string);

    //Player object interaction - If interaction is available for object, perform interaction. This is abstract virtual
    //function for all Space type objects. Player class interactions initiate opening/closing doors and picking up items.
    //Also used in allowing user to open locked doors if they have a key. Takes Space pointer as parameter for object
    //being interacted with.
    void interactObject(Space *inputSpace);

    //Search items in players item bag and return boolean value for whether or not item was in
    //item bag. If item is found, delete item and remove from bag.
    bool useItem(std::string);

    //Search items in players item bag and return boolean value if it exists or not. Does not remove item from bag like
    //useItem
    bool findItem(std::string inputItemSearch);

    //Set game win value from boolean parameter passed to function.
    void setWin(bool inputWin);

    //Get game win value and return boolean value
    bool getWin();

    //Output inventory to screen for user viewing
    void viewInventory();
};


#endif //PLAYER_HPP
