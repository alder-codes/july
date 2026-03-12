cmake_minimum_required(VERSION 4.0)
project(July)

set(CMAKE_CXX_STANDARD 11)

add_executable(July main.cpp classes/UserInput.cpp classes/AppDatabase.cpp classes/Item.cpp classes/DbItem.cpp)

target_link_libraries(July sqlite3)
