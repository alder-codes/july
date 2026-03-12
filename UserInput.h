#ifndef USERINPUT_H
#define USERINPUT_H

#include <vector>
#include <string>

class UserInput
{
  public:
    UserInput();

    std::string getLine();
    
    // Getters and setters for buffer
    std::string getBuffer() const;
    void setBuffer(const std::string& b);

    // Getters and setters for history
    std::vector<std::string> getHistory() const;
    void setHistory(const std::vector<std::string>& h);

  private:
    std::string buffer;
    std::vector<std::string> history;

};

#endif // USERINPUT_H
