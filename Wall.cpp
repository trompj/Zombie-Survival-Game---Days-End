/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Wall class is a child class of Space. This class represents all solid objects in the game, although most
 * specifically the walls of the game. Although it is also used in place of shelves and other environmental objects.
 * Variables: static const variables such as char for wallVisual to output to map when drawn and boolean values to set
 * the wall to solid (impassable) and interactable to false as it cannot be interacted with in the sense that it is
 * not an item.
 * Functions: Default constructor for wall object passes string value for "wall" and all static const values for
 * visualization, wallSolid, and interactable to Space constructor.
 * Default destructor for Wall object
 * interactObject - Overridden from abstract function in Space class - For Wall, a simple screen output describing
 * what is seen is displayed to user when user attempts to interact with the wall. Takes Space pointer, although Wall
 * interactObject function does not use the pointer in any output or functionality.
*/

#include "Wall.hpp"

//Default constructor for wall object passes string value for "wall" and all static const values for visualization,
//wallSolid, and interactable to Space constructor.
Wall::Wall() : Space ("wall", wallVisual, wallSolid, interactable) {}

//Default destructor for Wall object
Wall::~Wall() {}

//Wall object interaction - If interaction is available for object, perform interaction. This is abstract virtual
//function for all Space type objects. Non-interactable objects describe what is seen while interactable objects
//perform action if possible. For Wall, a simple screen output describing what is seen is displayed to user when
//user attempts to interact with the wall. Takes Space pointer, although Wall interactObject function does not
//use the pointer in any output or functionality.
void Wall::interactObject(Space *inputSpace) {
    if (!spaceInteract) {
        std::cout << "You gaze upon an aged looking " << this->getName() << ", a glimpse into what civilization used\n"
            << "to be." << std::endl;
    }
}