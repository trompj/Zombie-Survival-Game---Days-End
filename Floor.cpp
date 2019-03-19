/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Floor class is a child class of Space and is used to create the blank spaces of the map/world of the
 * game.
 * Variables: floorVisual: Sets the visualization of the space to a space character.
 * floorSolid: Sets the floor to passable and player can move to these spaces.
 * interactable: Item cannot be interacted with/picked up. Only viewed when interacted with.
 * Functions: Constructor does not take and parameters and sets Floor to "floor" as name and sets visuals/solidity/
 * interactability based on variables above.
 * Floor destructor is a default destructor
 * interactObject - Takes Space pointer, but does not interact with anything. Function outputs information about floor
 * space to user as if player is looking at it/examining it.
*/

#include "Floor.hpp"

//Default constructor for wall object.
Floor::Floor() : Space ("floor", floorVisual, floorSolid, interactable) {}

//Default destructor for wall object
Floor::~Floor() {}

//Floor object interaction - No interaction other than viewing of object and output of information to screen.
void Floor::interactObject(Space *inputSpace) {
    std::cout << "You see an aged " << this->getName() << " scuffed with dirt and traces of blood. You cannot interact "
        << "with it." << std::endl;
}