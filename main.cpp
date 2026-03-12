#include <iostream>
#include "UserInput.h"
#include "AppDatabase.h"

int main()
{
  AppDatabase db("test.db");
  if (db.open()) {
    std::cout << "Database opened successfully!" << std::endl;
    if (db.execute("CREATE TABLE IF NOT EXISTS test (id INTEGER PRIMARY KEY, name TEXT);")) {
        std::cout << "Table created or already exists." << std::endl;
    }
    db.close();
  } else {
    std::cerr << "Failed to open database." << std::endl;
    return 1;
  }

  return 0;
}
