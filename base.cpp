#include <sqlite3.h>
#include "base.h"

void initialization() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db); // deschidere baza de date si se verifica daca s-a deschis cu succes

    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }

    const char *sql = 
        "CREATE TABLE IF NOT EXISTS users ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    username TEXT UNIQUE NOT NULL,"
        "    password_hash TEXT NOT NULL,"
        "    salt TEXT NOT NULL"
        ");"
        "CREATE TABLE IF NOT EXISTS accounts ("
        "    id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "    user_id INTEGER NOT NULL,"
        "    app_name TEXT NOT NULL,"
        "    account_username TEXT NOT NULL,"
        "    account_password TEXT NOT NULL,"
        "    FOREIGN KEY (user_id) REFERENCES users(id) ON DELETE CASCADE"
        ");";

    rc = sqlite3_exec(db, sql, 0, 0, &zErrMsg); // se executa comanda sql

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Database initialized successfully!" << std::endl;
    }

    sqlite3_close(db); // inchidere baza de date
}
