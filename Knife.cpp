/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Knife class is a child class to GamePiece and thus a child class to Space as well. Class object represents
 * the knife item that can be used to kill one zombie before being lost and removed from bag. Knives are purely as self
 * defense.
 * Variables: knifeVisual - static const char for visualization of knife on map.
 * Functions: Constructor for Knife class takes two int values as parameters to represent location of row/col of knife and
 * passes both integers to GamePiece constructor, as well as string value for "knife" and the char visualization from
 * static const of knife object. Sets isItem to true.
 * Default destructor for Knife class.
 * interactObject - Overridden function from abstract Space class. For knife class, this function prints a string output
 * of the object and its use in game. Player class can then pick up the object and add to item bag. Takes Space pointer
 * as parameter, however this parameter is not used by knife class.
*/

#include "Knife.hpp"

//Constructor for Knife class takes two int values as parameters to represent location of row/col of knife and
//passes both integers to GamePiece constructor, as well as string value for "knife" and the char visualization from
//static const of knife object. Sets isItem to true.
Knife::Knife(int inputRow, int inputCol) : GamePiece("knife", knifeVisual, inputRow, inputCol) {
    isItem = true;
}

//Destructor for Key class
Knife::~Knife() {}

//Knife object interaction - If interaction is available for object, perform interaction. This is abstract virtual
//function for all Space type objects. Default functionality is defined in Space class to be called by non-interactable
//objects. Non-interactable objects describe what is seen while interactable objects perform action if possible.
//GamePiece class item Spaces are all interactable. For knife class, this function prints a string output
//of the object and its use in game. Player class can then pick up the object and add to item bag. Takes a Space
//pointer as parameter, however it is not used by knife class.
void Knife::interactObject(Space *inputSpace) {
    std::cout << "You see what appears to be a " << this->getName() << ". This would be handy against attacked. You\n"
        << "attempt to pick it up." << std::endl;
}