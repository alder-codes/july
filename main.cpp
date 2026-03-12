#include <iostream>
#include "UserInput.h"

int main()
{
  std::cout << "Enter something: ";
  UserInput input;
  std::string s = input.getLine();
  std::cout << "You entered: " << s << std::endl;
  return 0;
}