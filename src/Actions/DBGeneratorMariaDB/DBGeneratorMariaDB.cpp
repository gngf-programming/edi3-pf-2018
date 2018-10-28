#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <unordered_map>
#include <winsock.h>

#include <mysql.h>

#include <ComponentInterface.h>
#include <ActionInterface.h>


class DBGeneratorMariaDB : public ActionInterface, public ComponentInterface
{
    public:
        DBGeneratorMariaDB();
        virtual ~DBGeneratorMariaDB();
        int execute();

        //ComponentInterface
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        const char* MY_HOSTNAME;
        const char* MY_DATABASE;
        const char* MY_USERNAME;
        const char* MY_PASSWORD;
        const char* MY_SOCKET;
        enum {
            MY_PORT_NO = 3306,
            MY_OPT     = 0
        };
        MYSQL     *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        //ComponentInterface
        int referenceCounter;
        bool implemented;
};

DBGeneratorMariaDB::DBGeneratorMariaDB() : referenceCounter(0){
    MY_HOSTNAME = "localhost";
    MY_DATABASE = "compset";
    MY_USERNAME = "root";
    MY_PASSWORD = "root";
    MY_SOCKET   = NULL;
}

DBGeneratorMariaDB::~DBGeneratorMariaDB(){}

int DBGeneratorMariaDB::execute()
{
    MYSQL *mariadb = NULL; 
    
    mariadb = mysql_init(mariadb);

    // Intentar iniciar MySQL: 
    if (!mariadb) 
    {
        std::cout << "Init faild, out of memory?" << std::endl;
        return EXIT_FAILURE;
    }

    if( !mysql_real_connect(
                            mariadb, 
                            MY_HOSTNAME, 
                            MY_USERNAME, 
                            MY_PASSWORD, 
                            MY_DATABASE, 
                            MY_PORT_NO, 
                            MY_SOCKET,
                            MY_OPT
                            )
      )  
    { 
        // No se puede conectar con el servidor en el puerto especificado. 
        std::cout << "Imposible to connect to the database." << std::endl; 
        std::cout << "Error: " << mysql_error(mariadb) << std::endl;
        std::cout << "Error Nro: " << mysql_errno(mariadb) << std::endl; 
        mysql_close(mariadb); 
        return EXIT_FAILURE; 
    } else
    {
        std::cout << "Successful established connection" << std::endl; 
    }

    fstream query("querys.sql", ios::in);
    srting commands;
    if ( query.is_open() )
    {
        //realizar consultas
        do
        {
            getline(query, commands);
            if( mysql_query ( mariadb, commands ) )  
            {        
                // Error al realizar la consulta: 
                std::cout << "Error: " << mysql_error(mariadb) << std::endl;
                std::cout << "Error Nro: " << mysql_errno(mariadb) << std::endl; 
                mysql_close(mariadb); 
                rewind(stdin);      
            }
        }while( !query.eof() );
        query.close();
        return EXIT_SUCCESS;
    }else
    {
        query.close();
        std::cout << "Imposible read sql file. Check its existence in the right directory "<<std::endl;
        return EXIT_FAILURE;
    }

    // Hacer una consulta": 
     
    
    std::cout << "Error: " << mysql_error(mariadb) << std::endl;
    std::cout << "Error Nro: " << mysql_errno(mariadb) << std::endl;
    
    mysql_close(mariadb);
     
    getchar();    
    return EXIT_FAILURE;
}

/********************************************************************************************/
/*COMPONENT SECTION INTERFACE*/
bool DBGeneratorMariaDB::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "ActionInterface") ?
        implemented = true
            : implemented = false;
}

void* DBGeneratorMariaDB::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void DBGeneratorMariaDB::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create()
{
    return (ComponentInterface*) new DBGeneratorMariaDB;
}
