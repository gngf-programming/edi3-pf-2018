/********************************************************************************
* Copyright (c) 2018 Nano Nobile <crlsdnlnobile@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
*********************************************************************************/


#include <iostream>
#include <typeinfo>
#include <fstream>
#include <string>

#include <compset/ComponentFactory.h>
#include <compset/ComponentInterface.h>
#include <compset/DatabaseHandlerInterface.h>

#include <mysql.h>

typedef std::unordered_map< std::string, std::string > Row; 
typedef std::vector< Row > Table; 

class MdbDatabaseHandler : public DatabaseHandlerInterface , public ComponentInterface {

        public:
        MdbDatabaseHandler() ;
        virtual ~MdbDatabaseHandler() ;
        virtual bool getErrorStatus() ;
        virtual void prepareQuery( std::string query ) ;
        virtual void addParameter( int key, std::string value ) ;
        virtual void execute() ;
        virtual Row fetch() ;
        virtual Table fetchAll() ;

        bool implements( std::string interfaceName ) ; 
        void * getInstance() ;
        void release() ;

        private: 
        int referenceCounter;
        bool implemented;
        bool connected;

        MYSQL* conn;
        std::string data[5];
        std::string setQuery;
        const char* port;
        const char* user;
        const char* pass;
        const char* database;
        const char* host;
    
};

MdbDatabaseHandler::MdbDatabaseHandler() {

      /*  ifstream ini("config.ini");
        std::getline(ini, data[0]);
        std::getline(ini, data[1]);
        std::getline(ini, data[2]);
        std::getline(ini, data[3]);
        std::getline(ini, data[4]);
        ini.close();
        
        host = data[0].c_str();
        user = data[1].c_str();
        pass = data[2].c_str();
        database = data[3].c_str();
        port = data[4].c_str();
 */
        conn = mysql_init (NULL);
        mysql_real_connect( conn, "localhost", "root",
                                "yourpassword", "test", 3306, NULL, 0 );
 
        if(!getErrorStatus()){ connected = true; std::cout << "conectados a musql " << std::endl; }
        else { connected = false; std::cout << "error de conexion " << std::endl; }      
};

MdbDatabaseHandler::~MdbDatabaseHandler() {

        mysql_close(conn);
};

bool MdbDatabaseHandler::getErrorStatus() {

        return ( mysql_error(conn)[0] != '\0' ) ? true : false ;
};

void MdbDatabaseHandler::prepareQuery(std::string query){
    
    setQuery = query ;
    
};



void MdbDatabaseHandler::addParameter(int key, std::string value ){

    

};

void MdbDatabaseHandler::execute() {
    
    unsigned int result = 0;
    const char *setquery = setQuery.c_str();
    result = mysql_query(conn,setquery);

    if (result != 0) { printf("No se ha podido realiar la consulta ") ; }
    else if(result == 0 ) {printf ("consulta exitosa\n") ;}
    
};

Row MdbDatabaseHandler::fetch(){
    
    Row result ;
    return result ;

};

Table MdbDatabaseHandler::fetchAll(){
    Table result;
    return result ;
};

bool MdbDatabaseHandler::implements(std::string interfaceName) {
    return (interfaceName == "ComponentInterface" || interfaceName == "DatabaseHandlerInterface") ?
        implemented = true
            : implemented = false;
}

void* MdbDatabaseHandler::getInstance() {
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void MdbDatabaseHandler::release() {
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create() {
    return (ComponentInterface*) new MdbDatabaseHandler;
}






