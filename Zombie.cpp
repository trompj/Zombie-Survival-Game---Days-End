/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Zombie class object is a child class of GamePiece, which is a child class of Space. This class
 * represents all zombie objects in game and determines their movement around the board as well as their construction
 * and interaction with the world around them.
 * Variables: static const char zombieVisual represents the visualization of the zombie on the map.
 * int variable for movesLeft represents the movement counter for the zombies move pattern, which is move in a direction
 * twice, then change direction randomly, unless a solid object is encountered.
 * currentDirection represents the direction the zombie is facing and is randomly changed over time.
 * Space pointer currentSpace is set to nullptr and holds the Space that the zombie currently occupies on the map.
 * Functions: Constructor for zombie class to set up starting zombie attributes through GamePiece. Takes string value
 * for name of object, and two int values for the row/col of the zombie. These values are passed to GamePiece
 * constructor along with visualization of zombie. movesLeft, isAlive, and direction of zombie are all set to starting
 * values and currentSpace is set to null.
 * Default destructor setup to free allocated memory, however nothing specific is initiated in Zombie class.
 * interactObject - Zombie object interaction - If interaction is available for object, perform interaction. This is
 * an abstract virtual function for all Space type objects. Zombies do not interact with anything and are not interacted
 * with except through death, no action is performed. Takes Space pointer that is not used.
 * moveZombie - Determine zombies move to space and move pattern for zombie object upon each function call through
 * random number generation. If player is in a nearby space (up, down, left, right), move to attack player.
 * randomInt - Takes two integers as parameters and returns random integer from min through max values
 * setCurrentSpace - Set currentSpace Space pointer to Space pointer passed as parameter.
 * getCurrentSpace - Return currentSpace Space pointer.
*/

#include "Zombie.hpp"

//Constructor for zombie class to set up starting zombie attributes through GamePiece. Takes string value for
//name of object, and two int values for the row/col of the zombie. These values are passed to GamePiece constructor
//along with visualization of zombie. movesLeft, isAlive, and direction of zombie are all set to starting values and
//currentSpace is set to null.
Zombie::Zombie(std::string inputName, int inputRow, int inputCol) : GamePiece(zombieVisual,
        inputRow, inputCol, inputName) {
    //Default moves left value for zombie movement determination
    movesLeft = 2;

    //Set zombie to "alive" or active rather since zombies are undead.
    isAlive = true;

    //Default direction value. 1 for up, 2 for right, 3 for down, 4 for left
    currentDirection = 0;

    //Set current space to null as zombie has not been placed yet.
    currentSpace = nullptr;
}

//Default destructor - Removes all allocated memory if there is any for class
Zombie::~Zombie() {}

//Zombie object interaction - If interaction is available for object, perform interaction. This is abstract virtual
//function for all Space type objects. Zombies do not interact with anything and are not interacted with except through
//death, no action is performed. Takes Space pointer that is not used.
void Zombie::interactObject(Space *) {}

//Determine zombies move to space and move pattern for zombie object upon each function call through random number
//generation. If player is in a nearby space (up, down, left, right), move to attack player.
void Zombie::moveZombie() {
    //If player is in a nearby space that can be reached in one move, attack player
    if (this->getUp()->getName() == "player") {
        //If player has a knife in inventory, use on zombie to kill zombie and keep player alive.
        if(static_cast<Player*>(this->getUp())->useItem("knife")) {
            //Inform user of what occurred
            std::cout << "Zombie attack was stopped with a knife to its head!"
                << std::endl;

            //Set zombie to dead
            this->setAlive(false);
        }
        //No knife was in inventory, player dies.
        else {
            this->getUp()->setAlive(false);
        }
    }
    else if (this->getDown()->getName() == "player") {
        //If player has a knife in inventory, use on zombie to kill zombie and keep player alive.
        if(static_cast<Player*>(this->getDown())->useItem("knife")) {
            //Inform user of what occurred
            std::cout << "Zombie attack was stopped with a knife to its head!"
                      << std::endl;

            //Set zombie to dead
            this->setAlive(false);
        }
        //No knife was in inventory, player dies.
        else {
            this->getDown()->setAlive(false);
        }

    }
    else if (this->getRight()->getName() == "player") {
        //If player has a knife in inventory, use on zombie to kill zombie and keep player alive.
        if(static_cast<Player*>(this->getRight())->useItem("knife")) {
            //Inform user of what occurred
            std::cout << "Zombie attack was stopped with a knife to its head!"
                      << std::endl;

            //Set zombie to dead
            this->setAlive(false);
        }
        //No knife was in inventory, player dies.
        else {
            this->getRight()->setAlive(false);
        }
    }
    else if (this->getLeft()->getName() == "player") {
        //If player has a knife in inventory, use on zombie to kill zombie and keep player alive.
        if(static_cast<Player*>(this->getLeft())->useItem("knife")) {
            //Inform user of what occurred
            std::cout << "Zombie attack was stopped with a knife to its head!"
                      << std::endl;

            //Set zombie to dead
            this->setAlive(false);
        }
            //No knife was in inventory, player dies.
        else {
            this->getLeft()->setAlive(false);
        }
    }

    //Player is not in a nearby space, move as normal
    else {
        //If movesLeft is 0, determine new direction to move
        if (movesLeft <= 0) {
            //Find new direction
            currentDirection = randomInt(1, 4);

            //Reset movesLeft counter
            movesLeft = 2;
        }

        //If movesLeft is larger than zero, zombie moves in current directional value.
        //Perform movement of zombie in direction as long as the space moving to is not solid and
        //it cannot be interacted with such as a door or item. Set zombieMoved to true if zombie
        //was able to move.
        //Move zombie up 1.
        if (currentDirection == 1 && !this->getUp()->getSolid() && !this->getUp()->getInteract() &&
            this->getUp()->getName() != "zombie" && this->getUp()->getName() != "open space" &&
            this->getUp()->getName() != "open door") {
            //Move zombie in direction by 1 space
            this->row--;

            //Reduce moves left by 1
            movesLeft--;
        }
        //Move zombie right 1.
        else if (currentDirection == 2 && !this->getRight()->getSolid() && !this->getRight()->getInteract() &&
            this->getRight()->getName() != "zombie" && this->getRight()->getName() != "open space" &&
            this->getRight()->getName() != "open door") {
            //Move zombie in direction by 1 space
            this->col++;

            //Reduce moves left by 1
            movesLeft--;
        }
        //Move zombie down 1.
        else if (currentDirection == 3 && !this->getDown()->getSolid() && !this->getDown()->getInteract() &&
            this->getDown()->getName() != "zombie" && this->getDown()->getName() != "open space" &&
            this->getDown()->getName() != "open door") {
            //Move zombie in direction by 1 space
            this->row++;

            //Reduce moves left by 1
            movesLeft--;
        }
        //Move zombie left 1.
        else if (currentDirection == 4 && !this->getLeft()->getSolid() && !this->getLeft()->getInteract() &&
            this->getLeft()->getName() != "zombie" && this->getLeft()->getName() != "open space" &&
            this->getLeft()->getName() != "open door") {
            //Move zombie in direction by 1 space
            this->col--;

            //Reduce moves left by 1
            movesLeft--;
        }

        //Zombie was unable to move, set movesLeft to 0 so that new direction is chosen next round.
        else {
            movesLeft = 0;
        }
    }
}

//Takes two integers as parameters and returns random integer from min through max values
int Zombie::randomInt(int minVal, int maxVal) {
    //Obtain seed for random number engine
    std::random_device randomNumDevice;

    //Mersenne_twister_engine seeded with rd
    std::mt19937 generateNum(randomNumDevice());
    std::uniform_int_distribution<> dis(minVal, maxVal);

    return dis(generateNum);
}

//Set currentSpace Space pointer
void Zombie::setCurrentSpace(Space* inputSpace) {
    currentSpace = inputSpace;
}

//Get currentSpace Space pointer
Space* Zombie::getCurrentSpace() {
    return currentSpace;
}