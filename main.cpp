#include <iostream>
#include <vector>
#include <string>
#include "UserInput.h"
#include "AppDatabase.h"
#include "Item.h"
#include "DbItem.h"

#define APP_DB "./JULY_DATA.DB"

static bool input_on = true;

int main()
{
  AppDatabase db(APP_DB);
  if (!db.open()) {
    std::cerr << "Failed to open and initialize database." << std::endl;
    return 1;
  }
  std::cout << "Successfully connected to the database." << std::endl;
  
  DbItem dbItem(db);
  UserInput input;

  while ( input_on )
  {
    std::cout << "Would you like to create a new item? (yes/no): ";
    std::string response = input.getLine();

    if (response == "yes" || response == "y" || response == "YES" || response == "Y") {
      std::cout << "Enter the title for the new item: ";
      std::string title = input.getLine();

      // ID can be 0 or -1 as SQLite handles auto-increment for PRIMARY KEY
      // Item constructor handles the default timestamp if not provided.
      Item newItem(0, title);
      if (dbItem.create(newItem)) {
        std::cout << "Item '" << title << "' has been saved to the database." << std::endl;
      } else {
        std::cerr << "Failed to save the item to the database." << std::endl;
      }
    } else {
      std::cout << "No new item created." << std::endl;
      input_on = false;
    }
  }

  // List all items to show the current state
  std::vector<Item> allItems = dbItem.listAll();
  std::cout << "\nCurrent items in database (" << allItems.size() << "):" << std::endl;
  for (const auto& item : allItems) {
    std::cout << " - " << item.getID() << ": " << item.getTitle() << " (Created: " << item.getCreated() << ")" << std::endl;
  }

  db.close();
  return 0;
}
