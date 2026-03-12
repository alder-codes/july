#include "main.h"

int main()
{
  AppDatabase db(APP_DB);
  if (!db.open())
  {
    std::cerr << "Failed to open and initialize database." << std::endl;
    return 1;
  }
  std::cout << "Successfully connected to the database." << std::endl;

  DbItem dbItem(db);
  UserInput input;

  while (main_loop)
  {
    DisplayMenu();
    std::cout << "Your selection: ";
    std::string response = input.getLine();
    if (response == "0")
    {
      main_loop = false;
    } else if (response == "1")
    {
      std::cout << "Enter the title for the new item: ";
      std::string title = input.getLine();
      Item newItem(0, title);
      if (dbItem.create(newItem)) {
        std::cout << "Item '" << title << "' has been saved to the database." << std::endl;
      } else {
        std::cerr << "Failed to save the item to the database." << std::endl;
      }
    } else if (response == "2")
    {
      std::vector<Item> allItems = dbItem.listAll();
      DisplayItems(allItems);
    } else if (response == "3")
    {
      std::cout << "Enter the ID of the item to remove: ";
      std::string id_str = input.getLine();
      int id = std::stoi(id_str);
      dbItem.remove(id);
    } else if (response == "4")
    {
      std::cout << "Enter search query: ";
      std::string query = input.getLine();
      std::vector<Item> results = dbItem.search(query);
      DisplayItems(results);
    }
  }

  // List all items to show the current state
  std::vector<Item> allItems = dbItem.listAll();
  DisplayItems(allItems);

  db.close();
  return 0;
}


void DisplayMenu()
{
  std::cout << "0. Exit" << std::endl;
  std::cout << "1. Add item" << std::endl;
  std::cout << "2. List items" << std::endl;
  std::cout << "3. Remove item" << std::endl;
  std::cout << "4. Search items" << std::endl;
}


void DisplayItems(const std::vector<Item> &allItems)
{
  std::cout << "\nCurrent items in database (" << allItems.size() << "):" << std::endl;
  for (const auto &item: allItems)
  {
    std::cout << " - " << item.getID() << ": " << item.getTitle() << " (Created: " << item.getCreated() << ")" <<
        std::endl;
  }
}