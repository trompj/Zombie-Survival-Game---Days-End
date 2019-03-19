/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Door class is a child class of Space class and allows for placement of doors around map.
 * Door objects can be interacted with and open/close when player uses them. They can also be locked and may
 * require a key to open.
 * Variables: doorClosedVisual: Closed door visualization by char
 * doorClosedSolid: Door is set to solid by default for closed door.
 * interactable: Door is set to true for being interactable to open/close object.
 * isLocked: Door is set to false initially for isLocked for unlocked doors, but can be changed.
 * Functions: Door Constructor initialized through Space class and takes three paramaters. One string for
 * the map name that the door is in, and two int values for the row/column that door is in on map.
 * Door destructor is default destructor properties.
 * openDoor - Opens door and sets visualization/door properties to allow player to travel through them.
 * closeDoor - Closes door and sets visualization/door properties to make object solid in game.
 * getLocked - Returns boolean value for whether or not door is locked.
 * setLocked - Takes boolean value as parameter and sets locked status of door.
 * interactObject - Overridden function from abstract Space class. Takes Space pointer (although not used in
 * this class and checks whether door is open, closed, or locked and performs actions to open or close door and
 * inform user if door is locked.
*/

#ifndef DOOR_HPP
#define DOOR_HPP

#include "Space.hpp"

class Door : public Space {
private:
    //Map output visualization
    static const char doorClosedVisual = '|';

    static const bool doorClosedSolid = true,
                      interactable = true;

    bool isLocked = false;

public:
    //ExitPoint default constructor for door Spaces
    Door(std::string, int, int);

    //Default destructor for door object
    ~Door();

    //Open door - set visual to open and space to passable
    void openDoor();

    //Close door - set visual to closed and space to solid
    void closeDoor();

    //Return boolean value of whether door is locked or not
    bool getLocked();

    //Set boolean value of whether door is locked or not
    void setLocked(bool);

    //ExitPoint object interaction - If interaction is available for object, perform interaction. This is abstract virtual
    //function for all Space type objects. Non-interactable objects describe what is seen while interactable objects
    //perform action if possible
    void interactObject(Space *inputSpace);
};


#endif //DOOR_HPP
