#include "Item.h"
#include <ctime>

Item::Item(int id, const std::string& title, const std::string& created)
    : id(id), title(title), created(created) {
    if (this->created.empty()) {
        auto now = std::chrono::system_clock::now();
        std::time_t now_time = std::chrono::system_clock::to_time_t(now);
        std::tm tm_struct = *std::localtime(&now_time);
        char buffer[20];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tm_struct);
        this->created = std::string(buffer);
    }
}

int Item::getID() const {
    return id;
}

void Item::setID(int id) {
    this->id = id;
}

std::string Item::getTitle() const {
    return title;
}

void Item::setTitle(const std::string& title) {
    this->title = title;
}

std::string Item::getCreated() const {
    return created;
}

void Item::setCreated(const std::string& created) {
    this->created = created;
}
