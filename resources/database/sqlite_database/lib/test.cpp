#include <iostream>
#include "sqlite3.h"

using namespace std;

int main(int argc, char const *argv[])
{
	/* code */
	sqlite3 *db;
   int res;

   /* Open database */
   res = sqlite3_open("test.db", &db);
   if (res)
   {
      fprintf(stderr, "No puedo abrir la base de datos: %s\n", sqlite3_errmsg(db));
      exit(0);
   }
   else
   {
      fprintf(stderr, "Base de datos OK\n");
   }

   sqlite3_close(db);

   return 0;
}
