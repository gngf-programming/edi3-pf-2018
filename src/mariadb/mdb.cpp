
#include <iostream>
#include <windows.h>
#include <mysql.h>


 
MYSQL *conn;
int version = 1;

int main ( int argc, char *argv[] )
{
    conn = mysql_init ( NULL );
    mysql_real_connect ( conn, "localhost", "root",
            "qweqwe1", "test", 3306, NULL, 0 );
	version = mysql_get_server_version( conn );
	printf("\nMySQL Version = %d\n",version);
    mysql_close ( conn );

    system("pause");
    return 0;
}