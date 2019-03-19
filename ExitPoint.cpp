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

#include "ExitPoint.hpp"

//ExitPoint default constructor for door Spaces
ExitPoint::ExitPoint(int inputRow, int inputCol) : Space("exit point", doorClosedVisual, exitPtSolid, interactable) {
    row = inputRow;
    col = inputCol;

    gameEnd = false;
}

//Default destructor for door object
ExitPoint::~ExitPoint() {

}

//ExitPoint object interaction - No interaction performed in ExitPoint class from interaction. Exit point is interacted
//with through player class.
void ExitPoint::interactObject(Space *inputSpace) {}

/*FUNCTIONS BELOW ARE INCLUDED BUT CURRENTLY NOT IN USE*/
//Set gameEnd attribute. Takes boolean value to set gameEnd to as parameter.
void ExitPoint::setGameEnd(bool inputEnd) {
    gameEnd = inputEnd;
}

//Get gameEnd attribute, returns boolean value of gameEnd.
bool ExitPoint::getGameEnd() {
    return gameEnd;
}