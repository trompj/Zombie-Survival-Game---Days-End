/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: GamePiece class is a child class of space and a parent class to all items/players/zombies on the map.
 * Essentially the parent class of all objects that have some sort of interaction and/or move around the map.
 * Variables: objectPassable - static const to set object as passable to true if object can be moved on top of.
 * interactable - static const to set object to be interactive if it is an interactive object/item.
 * pickedUp - boolean value specific to GamePiece that is set to false initially to indicate that item is not picked
 * up. Set to to true once item is picked up from map by player.
 * Functions: Class has two constructors: Constructor to set up object attributes primarily for items that can be
 * interacted with. Takes string value for name of object, char for visualization, and row/column of object to be on
 * map. objectPassable and interactable static const values are passed to Space class for creation.
 * Constructor to set up object or player attributes - Takes char for visualization on board, row/col of object on
 * board, string for name of object, and passes all values to Space class for object creation.
 * Default Destructor
 * interactObject - Game piece/item object interaction - If interaction is available for object, perform interaction.
 * This is abstract virtual function for all Space type objects.  Non-interactable objects describe what is seen while
 * interactable objects perform action if possible. GamePiece class Spaces are all interactable.
 * setPickedUp - Set pickedUp boolean value based on bool passed as parameter.
 * getPickedUp - Return pickedUp boolean value to calling function
*/

#ifndef GAMEPIECE_HPP
#define GAMEPIECE_HPP

#include <iostream>
#include "Space.hpp"

//Class GamePiece entails all objects and people within the class
class GamePiece : public Space {
private:
    static const bool objectPassable = true,
                      interactable = true;

    //Set to true when player interacts with object and adds to inventory
    bool pickedUp = false;

public:
    //Constructor to set up object attributes primarily for items that can be interacted with. Takes string value
    //for name of object, char for visualization, and row/column of object to be on map. objectPassable and interactable
    //static const values are passed to Space class for creation.
    GamePiece(std::string, char, int, int);

    //Constructor to set up object or player attributes - Takes char for visualization on board, row/col of object on board,
    //string for name of object, and passes all values to Space class for object creation.
    GamePiece(char, int, int, std::string);

    //Default Destructor
    ~GamePiece();

    //Game piece/item object interaction - If interaction is available for object, perform interaction. This is abstract virtual
    //function for all Space type objects.  Non-interactable objects describe what is seen while interactable objects
    //perform action if possible. GamePiece class Spaces are all interactable.
    void interactObject(Space *inputSpace);

    //Set pickedUp boolean value based on bool passed as parameter.
    void setPickedUp(bool);

    //Return pickedUp boolean value to calling function
    bool getPickedUp();
};


#endif //GAMEPIECE_HPP
