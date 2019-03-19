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

#ifndef SPACE_HPP
#define SPACE_HPP

#include <iostream>

class Space {
protected:
    //Room information
    std::string spaceName;
    std::string mapName;

    //Boolean value for whether space object can be passed through or not
    bool solidSpace = true;

    //Boolean value for whether or not Space object can be interacted with (picked up)
    bool spaceInteract = false;

    //Boolean value for whether or not object is an item
    bool isItem = false;

    //Zombie/Player alive
    bool isAlive;

    //Space information/interactions
    Space* up;
    Space* down;
    Space* left;
    Space* right;

    //Position on board
    int row;
    int col;

    //Space visualization
    char spaceVisual = ' ';

public:
    //Constructor for space to create player/zombie related space object. Takes string for name of Space,
    //int values for location in row/col of map, and char visualization as parameters. Uses these values to set respective
    //attributes and sets all up/down/left/right pointers to null and the object to alive.
    Space(std::string, char, int, int);

    //Second Space constructor to create non-moveable space objects such as doors, floors, walls, and items. Takes string
    //for name of Space, char for visualization, and bool values for whether Space is solid and can be interacted
    //with/picked up. Constructor sets respective values received by parameter and sets all pointers to null.
    Space(std::string, char, bool, bool);

    //Abstract Space class virtual default destructor
    virtual ~Space();

    //Return string name of space
    std::string getName();

    //Return up space pointer
    Space* getUp();

    //Return down space pointer
    Space* getDown();

    //Return left space pointer
    Space* getLeft();

    //Return right space pointer
    Space* getRight();

    //Return current space pointer. NOT USED BUT LEFT IN CASE CHANGES ARE MADE.
    Space* getCurrent();

    //Return character visual
    char getVisual();

    //Set character visual - Such as if door is opened to change visualization. Takes char as parameter.
    void setVisual(char);

    //Set up space pointer. Takes Space pointer as parameter.
    void setUp(Space*);

    //Set down space pointer. Takes Space pointer as parameter.
    void setDown(Space*);

    //Set left space pointer. Takes Space pointer as parameter.
    void setLeft(Space*);

    //Set right space pointer. Takes Space pointer as parameter.
    void setRight(Space*);

    //Return int number of rows
    int getRows();

    //Return int number of cols
    int getCols();

    //Set number of rows. Takes int as parameter.
    void setRows(int);

    //Set number of cols. Takes int as parameter.
    void setCols(int);

    //Set solid space boolean value (whether space object can be passed through or not). Takes bool as parameter.
    void setSolid(bool);

    //Set space objects string name representation. Takes string as parameter
    void setName(std::string);

    //Return boolean value for solid space (whether space object can be moved through or not)
    bool getSolid();

    //Return whether or not object is interactable by bool value
    bool getInteract();

    //Return string value for map name that Space is in.
    std::string getMapName();

    //Set whether or not object is interactable, takes boolean value for change
    void setInteract(bool);

    //Space object interaction - If interaction is available for object, perform interaction. This is abstract virtual
    //function for all Space type objects. Non-interactable objects describe what is seen while interactable objects
    //perform action if possible. Takes Space pointer, however pointer is not used in this instance. This is a generic
    //version of interactObject and can be called, however all child classes override this abstract virtual function.
    virtual void interactObject(Space *inputSpace) = 0;

    //Return boolean value for whether Space object is an item or not
    bool getIsItem();

    //Set boolean alive status for zombies and players through bool parameter.
    void setAlive(bool inputAlive);

    //Get boolean alive status for zombies and players
    bool getAlive();

};


#endif //SPACE_HPP
