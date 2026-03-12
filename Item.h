#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>

class Item {
public:
    Item(int id, const std::string& title, const std::string& created = "");

    int getID() const;
    void setID(int id);

    std::string getTitle() const;
    void setTitle(const std::string& title);

    std::string getCreated() const;
    void setCreated(const std::string& created);

private:
    int id;
    std::string title;
    std::string created;
};

#endif // ITEM_H
