/* Author: Justin Tromp
 * Email: trompj@oregonstate.edu
 * Date Created: 02/08/2019
 * Description: Validation functions used in fantasy combat simulation.
 * validateInputRangeInt - Validate integer input from min through max parameters passed to function.
 * stringUpperCase - Takes string as parameter and returns string in all upper case.
 * validateMove - Accept/validate user input for control selection. Returns string of validated selection.
*/

#include "inputValidation.hpp"

//Validate integer input from min through max parameters passed to function
int validateInputRangeInt (int min, int max) {
    int userInput = 0;
    std::string userStringInput = " ";

    //Accept input from user
    getline(std::cin, userStringInput);

    //If input is an integer, store value in userInput
    if (std::all_of(userStringInput.begin(), userStringInput.end(), ::isdigit) && !userStringInput.empty()) {
        userInput = std::stoi(userStringInput);
    }

    bool inputNotValidated = false;
    //As long as user inputs non-digits, loop to request correct input
    while ((!std::all_of(userStringInput.begin(), userStringInput.end(), ::isdigit)) || inputNotValidated ||
           (userStringInput.empty()) || userInput < min || userInput > max) {

        //Change to true as user input must be validated before placing in userInput as integer
        inputNotValidated = true;

        //Re-prompt user for input
        std::cout << "Please enter a valid integer (i.e., without decimals) and within "
                     "the previously specified range." << std::endl;

        //Accept input from user
        getline(std::cin, userStringInput);

        //If conditions are met, move user input from string to integer variable and update input validation
        //boolean value to allow loop exit.
        if ((std::all_of(userStringInput.begin(), userStringInput.end(), ::isdigit)) && !userStringInput.empty()) {
            userInput = std::stoi(userStringInput);
            inputNotValidated = false;
        }
    }

    return userInput;
}

//Takes string value as parameter and capitalizes all letters, returning capitalized string value to
//calling function.
std::string stringUpperCase(std::string inputString) {
    //Capitalize all letters in user entered name to allow for easier entry
    for (unsigned count = 0; count < inputString.length(); count++) {
        inputString[count] = std::toupper(inputString[count]);
    }

    return inputString;
}

//Accept/validate user input for control selection. Returns string of validated selection.
std::string validateMove() {
    std::string userInput = "";

    std::cout << "Please enter a movement selection above, capitalization does not matter: ";

    bool inputValid = false;
    do {
        //Get user input
        getline(std::cin, userInput);

        std::cout << std::endl;

        //Capitalize userInput string for easier input
        for (unsigned count = 0; count < userInput.length(); count++) {
            userInput[count] = toupper(userInput[count]);
        }

        if (userInput == "W" || userInput == "S" || userInput == "A" || userInput == "D" || userInput == "I"
            || userInput == "E" || userInput == "Q") {
            inputValid = true;
        }

        else {
            std::cout << "Invalid selection, please enter one of the characters above to make a selection: ";
        }

    } while (!inputValid);

    return userInput;
}