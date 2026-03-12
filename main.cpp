#include <iostream>
#include "UserInput.h"
#include "AppDatabase.h"
#include "Item.h"
#include "DbItem.h"

int main()
{
  AppDatabase db("test.db");
  if (!db.open()) {
    std::cerr << "Failed to open database." << std::endl;
    return 1;
  }
  
  db.createItemsTable();
  DbItem dbItem(db);

  // Clear table for clean test
  db.execute("DELETE FROM items;");

  // Create
  Item item1(1, "First Item", "2026-03-12 15:00:00");
  Item item2(2, "Second Item", "2026-03-12 15:05:00");
  Item item3(3, "Default Time Item");
  dbItem.create(item1);
  dbItem.create(item2);
  dbItem.create(item3);

  // Read
  Item readItem = dbItem.read(1);
  std::cout << "Read Item 1: " << readItem.getTitle() << " (" << readItem.getCreated() << ")" << std::endl;

  Item readItem3 = dbItem.read(3);
  std::cout << "Read Item 3 (Default Time): " << readItem3.getTitle() << " (" << readItem3.getCreated() << ")" << std::endl;

  // Update
  readItem.setTitle("Updated First Item");
  dbItem.update(readItem);
  
  // List All
  std::vector<Item> allItems = dbItem.listAll();
  std::cout << "All items count: " << allItems.size() << std::endl;
  for (const auto& item : allItems) {
      std::cout << " - " << item.getID() << ": " << item.getTitle() << std::endl;
  }

  // Delete
  dbItem.remove(2);
  std::cout << "Items after deleting ID 2: " << dbItem.listAll().size() << std::endl;

  db.close();
  return 0;
}
