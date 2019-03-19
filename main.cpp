/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 03/12/2019
 * Description: Main function for Zombie game creates Game object and runs game by using Game class object to activate
 * runGame function to operate game until loss or user quits.
*/

#include <iostream>
#include "Game.hpp"

int main() {

    Game gameBegin;

    gameBegin.runGame();

    return 0;
}