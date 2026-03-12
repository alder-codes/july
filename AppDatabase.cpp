#include "AppDatabase.h"
#include <iostream>

AppDatabase::AppDatabase(const std::string& dbPath) : dbPath(dbPath), db(nullptr) {}

AppDatabase::~AppDatabase() {
    close();
}

bool AppDatabase::open() {
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true;
}

void AppDatabase::close() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool AppDatabase::execute(const std::string& sql) {
    char* zErrMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &zErrMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
        return false;
    }
    return true;
}

bool AppDatabase::createItemsTable() {
    return execute("CREATE TABLE IF NOT EXISTS items (id INTEGER PRIMARY KEY, title TEXT, created TEXT);");
}

sqlite3* AppDatabase::getHandle() const {
    return db;
}
