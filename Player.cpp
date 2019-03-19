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

#include "Player.hpp"
#include "Door.hpp"

//Constructor for player class to set up starting player attributes through GamePiece. Takes string input
//for player name and two int values for row/col that player is placed in. Passes all values to GamePiece class as well
//as player visualization. Within player constructor, player is set to alive and gameWin is set to false.
Player::Player(std::string inputName, int inputRow, int inputCol) : GamePiece(playerVisual,
        inputRow, inputCol, inputName) {

    //Set player to alive
    setAlive(true);

    //Set game win to false
    gameWin = false;
}

//Default destructor - Removes all allocated memory as needed
Player::~Player() {}


//Add object to player inventory and return boolean value of true or false if object is picked up/added. Takes string
//value of inventory item being added.
bool Player::addInventory(std::string inputInventoryItem) {
    bool itemPickedUp = false;
    int sizeInventory = static_cast<int>(inventory.size());

    //If inventory limit has not been reached, add item to bag and set item boolean value to picked up as true
    if (sizeInventory < maxInventory) {
        inventory.push_back(inputInventoryItem);

        itemPickedUp = true;

        std::cout << "A " << inputInventoryItem << " was added to your bag." << std::endl;
    }

    //If inventory limit is maxed out, do not add item to bag and output message to user.
    else {
        std::cout << "Your bag is full! Item cannot be picked up. Use an item to free space." << std::endl;
    }

    return itemPickedUp;
}


//Player object interaction - If interaction is available for object, perform interaction. This is abstract virtual
//function for all Space type objects. Player class interactions initiate opening/closing doors and picking up items.
//Also used in allowing user to open locked doors if they have a key. Takes Space pointer as parameter for object being
//interacted with.
void Player::interactObject(Space *inputSpace) {
    //Perform item function if there is any (such as open/close door)
    inputSpace->interactObject(inputSpace);

    //If locked door is encountered, request if user would like to use their key to open it, if they have one.
    if (inputSpace->getName() == "locked door" && findItem("key")) {
        std::cout << "Would you like to try using the key in your inventory to open the door?" << std::endl;
        std::cout << "1. Yes    2. No" << std::endl;

        //Validate user input
        int userSelection = validateInputRangeInt(1, 2);

        //Unlock door with key
        if (userSelection == 1) {
            //Use and delete item from inventory
            useItem("key");

            //Unlock door and output message to user.
            dynamic_cast<Door*>(inputSpace)->setLocked(false);
            dynamic_cast<Door*>(inputSpace)->setName("closed door");
            std::cout << "The door was unlocked and may be opened!" << std::endl;
        }
        //Do not use key and return item to bag.
        else {
            std::cout << "The key was returned to your bag." << std::endl;
        }
    }

    //If the exit point is reached, check to make sure player has items needed to end the game and set end game to true
    //if so.
    else if (inputSpace->getName() == "exit point" && useItem("medicine")) {
        this->setWin(true);
    }

    //Object is an item and can be picked up. If item is added to inventory, set item picked up bool to true
    else if (inputSpace->getIsItem()) {
        dynamic_cast<GamePiece*>(inputSpace)->setPickedUp(this->addInventory(inputSpace->getName()));
    }
}

//Search items in players item bag and return boolean value for whether or not item was in
//item bag. If item is found, delete item and remove from bag.
bool Player::useItem(std::string inputItemSearch) {
    bool itemFound = false;

    //Loop through inventory bag
    for (unsigned count = 0; count < inventory.size(); count++) {
        //If item is found in inventory, set itemFound to true and delete item from bag/remove from vector
        if (inventory[count] == inputItemSearch) {
            itemFound = true;

            //If medicine is being used, must be at exit point, do not need to output message about medicine being
            //used out of backpack.
            if (inputItemSearch == "medicine") {

            }
            //Item was used out of inventory/backpack, inform user.
            else {
                std::cout << "A " << inputItemSearch << " was used out of backpack and lost." << std::endl;
            }

            //Remove item from inventory
            inventory.erase(inventory.begin()+count);

            //Exit loop if item is found
            break;
        }
    }

    return itemFound;
}

//Search items in players item bag and return boolean value if it exists or not. Does not remove item from bag like
//useItem.
bool Player::findItem(std::string inputItemSearch) {
    bool itemFound = false;

    //Loop through inventory bag
    for (unsigned count = 0; count < inventory.size(); count++) {
        //If item is found in inventory, set itemFound to true and exit loop. Return itemFound to calling function.
        if (inventory[count] == inputItemSearch) {
            itemFound = true;

            //Exit loop if item is found
            break;
        }
    }

    return itemFound;
}

//Set game win value from boolean parameter passed to function.
void Player::setWin(bool inputWin) {
    gameWin = inputWin;
}

//Get game win value and return boolean value
bool Player::getWin() {
    return gameWin;
}

//Output inventory to screen for user viewing
void Player::viewInventory() {
    std::cout << "INVENTORY BAG" << std::endl;
    std::cout << "Max Number of Items:    " << maxInventory << std::endl;
    std::cout << "Number of Items:        " << inventory.size() << std::endl;
    std::cout << "Inventory Bag Contents: ";

    //If inventory size is more than 0, print inventory
    if (inventory.size() > 0) {
        //Loop through inventory bag and output contents to screen
        for (unsigned count = 0; count < inventory.size(); count++) {
            std::cout << stringUpperCase(inventory[count]);

            //If this is not the last item to be printed, print comma
            if ((count+1) != inventory.size()) {
                std::cout << ", ";
            }
        }
    }
    //If inventory is empty, output message saying that inventory is empty
    else {
        std::cout << "EMPTY";
    }

    std::cout << std::endl << std::endl;
}