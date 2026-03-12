#include "UserInput.h"
#include <iostream>

UserInput::UserInput()
{
  this->buffer = "";
  this->history = std::vector<std::string>();
}

std::string UserInput::getLine()
{
    std::string input;
    std::getline(std::cin, input);
    this->buffer = input;
    this->history.push_back(input);
    return input;
}

std::string UserInput::getBuffer() const {
    return this->buffer;
}

void UserInput::setBuffer(const std::string& b) {
    this->buffer = b;
}

std::vector<std::string> UserInput::getHistory() const {
    return this->history;
}

void UserInput::setHistory(const std::vector<std::string>& h) {
    this->history = h;
}
