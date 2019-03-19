/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: ExitPoint class is a child class of Space class and sets an end point for player to win game. Player
 * must have medication to be able to access ExitPoint and win game through Player class.
 * Variables: doorClosedVisual: Visualization of exit point by character.
 * exitPtSolid: Object is solid and should be interacted with from sides.
 * interactable: Set object to true as it is an interactable object.
 * gameEnd: Set to false initially for game not finished.
 * Functions: ExitPoint constructor creates ExitPoint object through Space constructor and takes two int parameters,
 * one for row of object and the second for the column of the object.
 * Default destructor for ExitPoint class.
 * interactObject - ExitPoint object interaction - No interaction performed in ExitPoint class from interaction.
 * Exit point is interacted with through player class.
 * getGameEnd - Returns gameEnd boolean value, although gameEnd is currently implemented through player class and is
 * unused.
 * setGameEnd - Sets gameEnd boolean value, although unused. Left in for possible future updates to game.
*/

#ifndef EXITPOINT_HPP
#define EXITPOINT_HPP


#include "Space.hpp"

class ExitPoint : public Space {
private:
    //Map output visualization
    static const char doorClosedVisual = '*';

    static const bool exitPtSolid = true,
                      interactable = true;

    bool gameEnd = false;

public:
    //ExitPoint default constructor for door Spaces
    ExitPoint(int, int);

    //Default destructor for door object
    ~ExitPoint();

    //ExitPoint object interaction - No interaction performed in ExitPoint class from interaction. Exit point is interacted
    //with through player class.
    void interactObject(Space *inputSpace);

    /*FUNCTIONS BELOW ARE INCLUDED BUT CURRENTLY NOT IN USE*/
    //Set gameEnd attribute. Takes boolean value to set gameEnd to as parameter.
    void setGameEnd(bool inputEnd);

    //Get gameEnd attribute, returns boolean value of gameEnd.
    bool getGameEnd();
};


#endif //EXITPOINT_HPP
