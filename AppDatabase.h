#ifndef APPDATABASE_H
#define APPDATABASE_H

#include <string>
#include <sqlite3.h>

class AppDatabase {
public:
    AppDatabase(const std::string& dbPath);
    ~AppDatabase();

    bool open();
    void close();
    bool execute(const std::string& sql);

private:
    std::string dbPath;
    sqlite3* db;
};

#endif // APPDATABASE_H
