#include <iostream>
#include <stdio.h>
#include "lib/sqlite3.h"

using namespace std;

const int nTables = 5;
bool VerifyTables(sqlite3 *);
bool status = 0;

using namespace std;

int main()
{
    int rc;
    sqlite3 *db;

    // Abrir base de datos
    rc = sqlite3_open("compset.db", &db);
    if(SQLITE_OK != rc)
    {
        cout << "Error: " << sqlite3_errmsg(db) << endl;
		return 1;
    }
    else
    {
        cout << "Database is ready to operate..." << sqlite3_errmsg(db) << endl;
    }

    !VerifyTables( db )? status = false : status = true;

    if (status)
    {
        cout << "Done Successfully" << endl;
    }
    else
    {
        cout << "Done with errors" << endl;
    }

    // Cerrar base de datos
    sqlite3_close(db);
    return 0;
}

bool VerifyTables(sqlite3 *db)
{
    char query[36];

    char *table[] = { "users", "roles", "actions", "users_has_roles", "roles_has_actions" };

    char *create[] = {
        //"PRAGMA foreign_keys = ON;"
        "CREATE TABLE IF NOT EXISTS users ("
          "id_users INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
          "identifier TEXT,"
          "password_hash TEXT);",

        "CREATE TABLE IF NOT EXISTS roles("
          "id_roles INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,"
          "name TEXT,"
          "description TEXT);",

        "CREATE TABLE IF NOT EXISTS actions("
          "id_actions INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,"
          "name TEXT);",

        "CREATE TABLE IF NOT EXISTS users_has_roles("
          "id_users_has_roles INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,"
          "users_id INTEGER NOT NULL,"
          "roles_id INTEGER NOT NULL,"
          "FOREIGN KEY (users_id) REFERENCES users(id_users)"
          "ON DELETE CASCADE "
          "ON UPDATE SET NULL,"
          "FOREIGN KEY (roles_id) REFERENCES roles(id_roles) "
          "ON DELETE CASCADE "
          "ON UPDATE SET NULL);",

        "CREATE TABLE IF NOT EXISTS roles_has_actions("
          "id_roles_has_actions INTEGER NOT NULL UNIQUE PRIMARY KEY AUTOINCREMENT,"
          "actions_id INTEGER NOT NULL,"
          "roles_id INTEGER NOT NULL,"
          "FOREIGN KEY (actions_id) REFERENCES actions(id_actions)"
          "ON DELETE CASCADE "
          "ON UPDATE SET NULL,"
          "FOREIGN KEY (roles_id) REFERENCES roles(id_roles) "
          "ON DELETE CASCADE "
          "ON UPDATE SET NULL);"
    };

    for(int i = 0; i < nTables; i++)
    {
        sprintf(query, "SELECT COUNT(*) FROM %s;", table[i]);
        if(SQLITE_OK != sqlite3_exec(db, query, 0, 0, 0))
        {
            cout << "La tabla " << table[i] << " no existe." << endl;
            if(SQLITE_OK != sqlite3_exec(db, create[i], 0, 0, 0))
            {
               cout << "Error al crear la tabla " << table[i] <<endl;
               cout << "Error: "<< sqlite3_errmsg(db) << endl;
               return false;
            }
            else
            {
                cout << "La tabla " << table[i] << " fue creada con exito..." <<endl;
            };
        }
        else
        {
            cout << "La tabla " << table[i] << " ya existe..." << endl;
        }
    }
    return true;
};

