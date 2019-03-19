/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 02/08/2019
 * Description: Validation functions used in fantasy combat simulation.
 * validateInputRangeInt - Validate integer input from min through max parameters passed to function.
 * stringUpperCase - Takes string as parameter and returns string in all upper case.
 * validateMove - Accept/validate user input for control selection. Returns string of validated selection.
*/

#ifndef INPUTVALIDATION_HPP
#define INPUTVALIDATION_HPP

#include <iostream>
#include <string>
#include <algorithm>

//Validate integer input from min through max parameters passed to function
int validateInputRangeInt (int min, int max);

//Takes string value as parameter and capitalizes all letters, returning capitalized string value to
//calling function.
std::string stringUpperCase(std::string inputString);

//Accept/validate user input for control selection. Returns string of validated selection.
std::string validateMove();

#endif //INPUTVALIDATION_HPP
