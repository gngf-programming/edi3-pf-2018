#include <stdio.h>  
#include <iostream>
#include <windows.h>
#include "C:\Program Files (x86)\MariaDB\MariaDB Connector C\include\mysql.h"


 
MYSQL *conn;
int version = 1;

int main ( int argc, char *argv[] )
{
    conn = mysql_init ( NULL );
    mysql_real_connect ( conn, "localhost", "root",
            "password", "test", 3306, NULL, 0 );
	version = mysql_get_server_version( conn );
	printf("\nMySQL Version = %d\n",version);
    mysql_close ( conn );
    return 0;
}