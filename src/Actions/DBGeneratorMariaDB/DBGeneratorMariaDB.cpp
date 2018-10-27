#include <iostream>
#include <unordered_map>
#include <string>
#include <winsock.h>
#include "./include/mysql.h"

#include <compset/ComponentInterface.h>
#include <compset/ActionInterface.h>


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
        //ComponentInterface
        int referenceCounter;
        bool implemented;
};

DBGeneratorMariaDB::DBGeneratorMariaDB() : referenceCounter(0){}

DBGeneratorMariaDB::~DBGeneratorMariaDB(){}

int DBGeneratorMariaDB::execute()
{
    MYSQL *myData; 
  
    // Intentar iniciar MySQL: 
    if(!(myData = mysql_init(0)))  
    { 
        // Imposible crear el objeto myData 
        return 1; 
    } 

    const char* usuario = ("root"); 
    const char* clave = ("root"); 
    const char* database_name = ("compset");
    if(!mysql_real_connect(myData, "127.0.0.1", usuario, clave, database_name, mysql_port, NULL, 0))  
    { 
        // No se puede conectar con el servidor en el puerto especificado. 
        std::cout << "Imposible conectar con servidor mysql en el puerto " << mysql_port << std::endl; 
        mysql_close(myData); 
        return 1; 
    } 
     
    if(mysql_ping(myData))  
    { 
        std::cout << "Error: conexión imposible" << std::endl; 
        mysql_close(myData); 
    } 

    // Hacer una consulta con el comando "SELECT * FROM users": 
    if( mysql_query (   myData, 
                        "SELECT * FROM users" 
                    ) 
      )  
    { 
        // Error al realizar la consulta: 
        std::cout << "ERROR: " << mysql_error(myData) << std::endl; 
        mysql_close(myData); 
        rewind(stdin); 
        getchar(); 
        return 2; 
    } 
    
    return 0;
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

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new DBGeneratorMariaDB;
}
