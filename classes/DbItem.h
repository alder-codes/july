#ifndef DBITEM_H
#define DBITEM_H

#include <vector>
#include "Item.h"
#include "AppDatabase.h"

class DbItem {
public:
    DbItem(AppDatabase& db);

    bool create(const Item& item);
    Item read(int id);
    bool update(const Item& item);
    bool remove(int id);
    std::vector<Item> listAll();
    std::vector<Item> search(const std::string& query);

  private:
    AppDatabase& db;
};

#endif // DBITEM_H
