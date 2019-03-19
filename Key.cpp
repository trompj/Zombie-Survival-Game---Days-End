/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Key class is a child class to GamePiece and thus a child class to Space as well. Class object represents
 * the key to open the door for the pharmacy in game to retrieve the medication.
 * Variables: keyVisual - static const char for visualization of key on map.
 * Functions: Constructor for Key class takes two int values as parameters to represent location of row/col of key and
 * passes both integers to GamePiece constructor, as well as string value for "key" and the char visualization from
 * static const of key object. Sets isItem to true.
 * Default destructor for Key class.
 * interactObject - Overridden function from abstract Space class. For key class, this function prints a string output
 * of the object and its use in game. Player class can then pick up the object and add to item bag. Takes a Space
 * pointer as parameter, however it is not used in Key class.
*/

#include "Key.hpp"

//Constructor for Key class takes two int values as parameters to represent location of row/col of key and passes
//both integers to GamePiece constructor, as well as string value for "key" and the char visualization from static const
//of key object. Sets isItem to true.
Key::Key(int inputRow, int inputCol) : GamePiece("key", keyVisual, inputRow, inputCol) {
    isItem = true;
}

//Default destructor for Key class
Key::~Key() {}

//Key object interaction - If interaction is available for object, perform interaction. This is abstract virtual
//function for all Space type objects. Non-interactable objects describe what is seen while interactable objects
//perform action if possible. GamePiece class Spaces are all interactable.Overridden function from abstract Space
//class. For key class, this function prints a string output of the object and its use in game. Player class can
//then pick up the object and add to item bag.  Takes a Space pointer as parameter, however it is not used in Key class.
void Key::interactObject(Space *inputSpace) {
    std::cout << "You see what appears to be a " << this->getName() << ". Perhaps you can unlock a door with it! You\n"
        << "attempt to pick it up." << std::endl;
}