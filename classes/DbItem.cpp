#include "DbItem.h"
#include <iostream>

DbItem::DbItem(AppDatabase& db) : db(db) {}

bool DbItem::create(const Item& item) {
    sqlite3_stmt* stmt;
    const char* sql = "INSERT INTO items (title, created) VALUES (?, ?);";
    if (sqlite3_prepare_v2(db.getHandle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt, 1, item.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, item.getCreated().c_str(), -1, SQLITE_TRANSIENT);
    
    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

Item DbItem::read(int id) {
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, title, created FROM items WHERE id = ?;";
    if (sqlite3_prepare_v2(db.getHandle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return Item(0, "", "");
    }
    sqlite3_bind_int(stmt, 1, id);
    
    Item item(0, "", "");
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        int itemId = sqlite3_column_int(stmt, 0);
        const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* created = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        item = Item(itemId, title ? title : "", created ? created : "");
    }
    sqlite3_finalize(stmt);
    return item;
}

bool DbItem::update(const Item& item) {
    sqlite3_stmt* stmt;
    const char* sql = "UPDATE items SET title = ?, created = ? WHERE id = ?;";
    if (sqlite3_prepare_v2(db.getHandle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_text(stmt, 1, item.getTitle().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, item.getCreated().c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, item.getID());
    
    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

bool DbItem::remove(int id) {
    sqlite3_stmt* stmt;
    const char* sql = "DELETE FROM items WHERE id = ?;";
    if (sqlite3_prepare_v2(db.getHandle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    
    bool success = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return success;
}

std::vector<Item> DbItem::listAll() {
    std::vector<Item> items;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, title, created FROM items;";
    if (sqlite3_prepare_v2(db.getHandle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return items;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* created = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        items.emplace_back(id, title ? title : "", created ? created : "");
    }
    sqlite3_finalize(stmt);
    return items;
}

std::vector<Item> DbItem::search(const std::string& query) {
    std::vector<Item> items;
    sqlite3_stmt* stmt;
    const char* sql = "SELECT id, title, created FROM items WHERE title LIKE ?;";
    if (sqlite3_prepare_v2(db.getHandle(), sql, -1, &stmt, nullptr) != SQLITE_OK) {
        return items;
    }

    std::string likeQuery = "%" + query + "%";
    sqlite3_bind_text(stmt, 1, likeQuery.c_str(), -1, SQLITE_TRANSIENT);

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* created = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        items.emplace_back(id, title ? title : "", created ? created : "");
    }
    sqlite3_finalize(stmt);
    return items;
}
