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

  private:
    AppDatabase& db;
};

#endif // DBITEM_H
