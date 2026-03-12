#ifndef JULY_MAIN_H
#define JULY_MAIN_H

#include <iostream>
#include <vector>
#include <string>
#include "classes/UserInput.h"
#include "classes/AppDatabase.h"
#include "classes/Item.h"
#include "classes/DbItem.h"

#define APP_DB "../data/JULY_DATA.DB"

void DisplayMenu();
void DisplayItems(const std::vector<Item> &allItems);

static bool main_loop = true;


#endif //JULY_MAIN_H