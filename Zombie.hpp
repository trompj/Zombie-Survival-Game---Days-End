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

#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include "GamePiece.hpp"
#include "Player.hpp"
#include <random>
#include <algorithm>

class Zombie : public GamePiece {
private:
    static const char zombieVisual = 'z';

    int movesLeft = 2;
    int currentDirection = 0;

    //Space that zombie is currently occupying on map
    Space* currentSpace = nullptr;

public:
    //Constructor for zombie class to set up starting zombie attributes through GamePiece. Takes string value for
    //name of object, and two int values for the row/col of the zombie. These values are passed to GamePiece constructor
    //along with visualization of zombie. movesLeft, isAlive, and direction of zombie are all set to starting values and
    //currentSpace is set to null.
    Zombie(std::string, int, int);

    //Default destructor
    ~Zombie();

    //Zombie object interaction - If interaction is available for object, perform interaction. This is abstract virtual
    //function for all Space type objects. Zombies do not interact with anything and are not interacted with except through
    //death, no action is performed. Takes Space pointer that is not used.
    void interactObject(Space *);

    //Determine zombies move to space and move pattern for zombie object upon each function call through random number
    //generation. If player is in a nearby space (up, down, left, right), move to attack player.
    void moveZombie();

    //Takes two integers as parameters and returns random integer from min through max values
    int randomInt(int, int);

    //Set currentSpace Space pointer to Space pointer passed as parameter
    void setCurrentSpace(Space*);

    //Return currentSpace Space pointer
    Space* getCurrentSpace();
};

#endif //ZOMBIE_HPP
