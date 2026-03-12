#include "UserInput.h"
#include <iostream>

UserInput::UserInput() {}

std::string UserInput::getLine() {
    std::string input;
    std::getline(std::cin, input);
    return input;
}
