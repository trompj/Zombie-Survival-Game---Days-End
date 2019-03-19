/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Knife class is a child class to GamePiece and thus a child class to Space as well. Class object represents
 * the knife item that can be used to kill one zombie before being lost and removed from bag. Knives are purely as self
 * defense.
 * Variables: medicineVisual - static const char for visualization of medicine on map.
 * Functions: Constructor for Medicine - Takes row/col integer values as parameters and passes values to GamePiece
 * class for position of item. String value "medicine" and char visualization from static const are also passed to
 * Space constructor and isItem is set to true.
 * Default destructor for Medicine
 * interactObject - Message is output to user informing them of what is encountered and that the player is going
 * to attempt to pick it up. If it is picked up, user is informed of such through Player class.
*/

#ifndef MEDICINE_HPP
#define MEDICINE_HPP

#include "GamePiece.hpp"

class Medicine : public GamePiece {
private:
    static const char medicineVisual = 'm';

public:
    //Constructor for Medicine - Takes row/col integer values as parameters and passes values to GamePiece class for
    //position of item. String value "medicine" and char visualization from static const are also passed to Space constructor
    //and isItem is set to true.
    Medicine(int, int);

    //Default destructor for Medicine
    ~Medicine();

    //Medicine object interaction - If interaction is available for object, perform interaction. This is abstract virtual
    //function for all Space type objects. Non-interactable objects describe what is seen while interactable objects
    //perform action if possible. GamePiece class Spaces are all interactable. For Medicine class, interaction outputs
    //what is encountered and informs user that they are attempting to pick it up.
    void interactObject(Space *inputSpace);
};

#endif //MEDICINE_HPP
