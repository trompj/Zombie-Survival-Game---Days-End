/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Space class is the parent class to all aspects of the game that exist within the maps. Map class
 * objects are made up of Space objects to create the interactive and moving world we see. Space objects can be Floors,
 * Walls, Zombies, and more.
 * Variables: String values for name of Space and name of Map that space is located in.
 * Boolean values for whether or not space is solid, can be interacted with (picked up), is an item, and whether or not
 * it is alive (zombies/players).
 * Each Space object has four pointers to up, down, left, and right which is used to point to other Space objects
 * surrounding it. Space objects such as outer walls point to nullptr if there is the edge of the map.
 * int values for row/col, used to indicate where some objects are on map.
 * char spaceVisualization to indicate what the Space looks like when the map is drawn.
 * Functions: Constructor #1 for space to create player/zombie related space object. Takes string for name of Space, int
 * values for location in row/col of map, and char visualization as parameters. Uses these values to set respective
 * attributes and sets all up/down/left/right pointers to null and the object to alive.
 * Constructor #2 creates non-moveable space objects such as doors, floors, walls, and items. Takes string for name of
 * Space, char for visualization, and bool values for whether Space is solid and can be interacted with/picked up.
 * Constructor sets respective values received by parameter and sets all pointers to null.
 * Default Destructor - Abstract Space class virtual default destructor
 * getName - Return string name of space
 * getUp - Return up space pointer
 * getDown - Return down space pointer
 * getLeft - Return left space pointer
 * getRight - Return right space pointer
 * getCurrent - Return current space pointer. NOT USED BUT LEFT IN CASE CHANGES ARE MADE OR THERE ARE ADDITIONS.
 * getVisual - Return character visual
 * setVisual - Set character visual - Such as if door is opened to change visualization. Takes char as parameter.
 * setUp - Set up space pointer. Takes Space pointer as parameter.
 * setDown - Set down space pointer. Takes Space pointer as parameter.
 * setLeft - Set left space pointer. Takes Space pointer as parameter.
 * setRight - Set right space pointer. Takes Space pointer as parameter.
 * getRows - Return int number of rows
 * getCols - Return int number of cols
 * setRows - Set number of rows. Takes int as parameter.
 * setCols - Set number of cols. Takes int as parameter.
 * setSolid - Set solid space boolean value (whether space object can be passed through or not). Takes bool as parameter.
 * setName - Set space objects string name representation. Takes string as parameter.
 * getSolid - Return boolean value for solid space (whether space object can be moved through or not)
 * getInteract - Return whether or not object is interactable by bool value
 * getMapName - Return string value for map that space is in.
 * setInteract - Set whether or not object is interactable, takes boolean value for change
 * interactObject - Space object interaction - If interaction is available for object, perform interaction. This is
 * abstract virtual function for all Space type objects. Non-interactable objects describe what is seen while
 * interactable objects perform action if possible. Takes Space pointer, however pointer is not used in this
 * instance. This is a generic version of interactObject and can be called, however all child classes override this
 * abstract virtual function.
 * getIsItem - Return boolean value for whether Space object is an item or not
 * setAlive - Set boolean alive status for zombies and players through bool parameter.
 * getAlive - Get boolean alive status for zombies and players
*/

#include "Space.hpp"
#include "Player.hpp"

//Constructor for space to create player/zombie related space object. Takes string for name of Space,
//int values for location in row/col of map, and char visualization as parameters. Uses these values to set respective
//attributes and sets all up/down/left/right pointers to null and the object to alive.
Space::Space(std::string inputName, char inputVisual, int inputRow, int inputCol) {
    //String value for space type
    spaceName = inputName;

    //Row/column of player or door
    row = inputRow;
    col = inputCol;

    //Visualization character on map
    spaceVisual = inputVisual;

    //Set to alive initially
    isAlive = true;

    up = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;
}


//Second Space constructor to create non-moveable space objects such as doors, floors, walls, and items. Takes string
//for name of Space, char for visualization, and bool values for whether Space is solid and can be interacted
//with/picked up. Constructor sets respective values received by parameter and sets all pointers to null.
Space::Space(std::string inputName, char inputVisual, bool inputSolid, bool inputInteractable) {
    //Declare space name and name of map it is located in (only for doors, "" for player)
    spaceName = inputName;

    //Set visualization
    spaceVisual = inputVisual;

    //Set passable status for object
    solidSpace = inputSolid;

    //Set ability to interact with space to false (walls and blank space objects)
    spaceInteract = inputInteractable;

    up = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;
}

//Abstract Space class virtual default destructor
Space::~Space() {}

//Return string name of space
std::string Space::getName() {
    return spaceName;
}

//Return up space pointer
Space* Space::getUp() {
    return up;
}

//Return down space pointer
Space* Space::getDown() {
    return down;
}

//Return left space pointer
Space* Space::getLeft() {
    return left;
}

//Return right space pointer
Space* Space::getRight() {
    return right;
}

//Return int number of rows
int Space::getRows() {
    return row;
}

//Return int number of cols
int Space::getCols() {
    return col;
}

//Set number of rows. Takes int as parameter.
void Space::setRows(int rowInput) {
    row = rowInput;
}

//Set number of cols. Takes int as parameter.
void Space::setCols(int colInput) {
    col = colInput;
}

//Set up space pointer. Takes Space pointer as parameter.
void Space::setUp(Space* inputSpace) {
    up = inputSpace;
}

//Set down space pointer. Takes Space pointer as parameter.
void Space::setDown(Space* inputSpace) {
    down = inputSpace;
}

//Set left space pointer. Takes Space pointer as parameter.
void Space::setLeft(Space* inputSpace) {
    left = inputSpace;
}

//Set right space pointer. Takes Space pointer as parameter.
void Space::setRight(Space* inputSpace) {
    right = inputSpace;
}

//Return character visual
char Space::getVisual() {
    return spaceVisual;
}

//Set character visual - Such as if door is opened to change visualization. Takes char as parameter.
void Space::setVisual(char inputVisual) {
    spaceVisual = inputVisual;
}

//Set solid space boolean value (whether space object can be passed through or not). Takes bool as parameter.
void Space::setSolid(bool inputSolid) {
    solidSpace = inputSolid;
}

//Set space objects string name representation. Takes string as parameter.
void Space::setName(std::string inputName) {
    spaceName = inputName;
}

//Return boolean value for solid space (whether space object can be moved through or not)
bool Space::getSolid() {
    return solidSpace;
}

//Return whether or not object is interactable by bool value
bool Space::getInteract() {
    return spaceInteract;
}

//Set whether or not object is interactable, takes boolean value for change
void Space::setInteract(bool inputInteract) {
    spaceInteract = inputInteract;
}

//Space object interaction - If interaction is available for object, perform interaction. This is abstract virtual
//function for all Space type objects. Non-interactable objects describe what is seen while interactable objects
//perform action if possible. Takes Space pointer, however pointer is not used in this instance. This is a generic
//version of interactObject and can be called, however all child classes override this abstract virtual function.
void Space::interactObject(Space *inputSpace) {
    if (!spaceInteract) {
        std::cout << "This is just a " << this->getName() << ". You cannot interact with it." << std::endl;
    }
}

//Return current space pointer - NOT USED BUT LEFT IN CASE CHANGES ARE MADE.
Space* Space::getCurrent() {
    return this;
}

//Return string value for map name that Space is in.
std::string Space::getMapName() {
    return mapName;
}

//Return boolean value for whether Space object is an item or not
bool Space::getIsItem() {
    return isItem;
}

//Set alive status for zombies and players
void Space::setAlive(bool inputAlive) {
    isAlive = inputAlive;
}

//Get alive status for zombies and players
bool Space::getAlive() {
    return isAlive;
}