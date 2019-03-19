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

#ifndef FLOOR_HPP
#define FLOOR_HPP

#include "Space.hpp"

class Floor : public Space {
private:
    static const char floorVisual = ' ';
    static const bool floorSolid = false,
                      interactable = false;

public:
    //Constructor does not take and parameters and sets Floor to "floor" as name and sets
    //visuals/solidity/interactability based on variables above.
    Floor();

    //Default destructor for floor object
    ~Floor();

    //Floor object interaction - If interaction is available for object, perform interaction. This is abstract virtual
    //function for all Space type objects. Non-interactable objects describe what is seen while interactable objects
    //perform action if possible
    void interactObject(Space *inputSpace);
};


#endif //FLOOR_HPP
