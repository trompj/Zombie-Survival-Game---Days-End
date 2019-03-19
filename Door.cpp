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

#include "Door.hpp"

//ExitPoint default constructor for door Spaces
Door::Door(std::string inputMapName, int inputRow, int inputCol) : Space("closed door", doorClosedVisual,
        doorClosedSolid, interactable) {
    mapName = inputMapName;

    //Set rows and columns of door objects
    row = inputRow;
    col = inputCol;

    isLocked = false;
}

//Default destructor for door object
Door::~Door() {}

//Open door - set visual to open and space to passable
void Door::openDoor() {
    //ExitPoint set to passable
    setSolid(false);

    //Change door visual to open
    setVisual('/');

    //Set door string description to open
    setName("open door");
}

//Close door - set visual to closed and space to solid
void Door::closeDoor() {
    //ExitPoint set to solid
    setSolid(true);

    //Change door visual to closed
    setVisual('|');

    //Set door string description to closed
    setName("closed door");
}

//Door object interaction - If interaction is available for object, perform interaction. This is abstract virtual
//function for all Space type objects. Non-interactable objects describe what is seen while interactable objects
//perform action if possible
void Door::interactObject(Space *inputSpace) {

    //If door is closed (whether locked or just closed) output same message.
    if (this->getName() == "closed door" || this->getName() == "locked door") {
        std::cout << "You see a closed door and reach for the handle." << std::endl;
    }

    //If door is open, output that door is open instead.
    else {
        //If this is an open alley, output message informing user of such.
        if (this->getName() == "open space") {
            std::cout << "You reached an open corridor, you may freely pass through." << std::endl;
        }
        //This is a door and you reach for handle
        else {
            std::cout << "You see a " << this->getName() << " and reach for the handle." << std::endl;
        }
    }

    //If door is interactable, perform opening or closing action unless it is locked, display message informing user
    //If the door is locked, inform user that key is needed
    if (this->isLocked) {
        std::cout << "The door is locked, you must have a key to enter!" << std::endl;
    }

    //Open or close door depending on current door status.
    else if (this->getInteract()) {
        //Set door to open or closed based on current status
        //If door is closed, open it.
        if (this->getVisual() == '|') {
            openDoor();
            std::cout << "You pull the door open." << std::endl;
        }

        //ExitPoint is already open, close it.
        else {
            closeDoor();
            std::cout << "You pull the door closed." << std::endl;
        }
    }

}

//Return boolean value of whether door is locked or not
bool Door::getLocked() {
    return isLocked;
}

//Set boolean value of whether door is locked or not
void Door::setLocked(bool inputLocked) {
    isLocked = inputLocked;
}
