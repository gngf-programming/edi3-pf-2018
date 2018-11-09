/*********************************************************************************
* Copyright (c) 2018 Nano Nobile <crlsdnlnobile@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
*******************************************************************************/
#include "mdb_database.h"

MdbDatabaseHandler::MdbDatabaseHandler() {

        ifstream ini("config.ini");
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

        conn = mysql_init (NULL);
        mysql_real_connect( conn, host, user,
                                pass, database, 3306, NULL, 0 );
        if(!getErrorStatus()){ connected = true; }
        else { connected = false; }       
};

MdbDatabaseHandler::~MdbDatabaseHandler() {

        mysql_close(conn);
};

bool MdbDatabaseHandler::getErrorStatus() {

        return ( mysql_error(conn)[0] != '\0' ) ? true : false ;
};

DatabaseHandlerInterface* MdbDatabaseHandler::setQuery(std::string query){
    
    DatabaseHandlerInterface* rquery;
    rquery = (DatabaseHandlerInterface*) query;
    return rquery ;

};

DatabaseHandlerInterface* MdbDatabaseHandler::setStoredProcedure(std::string storedProcedure){
   
    DatabaseHandlerInterface* r = NULL ;
    return r ;

};

DatabaseHandlerInterface* MdbDatabaseHandler::addParameter(std::string key, std::string value){
        DatabaseHandlerInterface* r = NULL ;
        return r ;

};

void MdbDatabaseHandler::execQuery() {
    
    unsigned int result = 0;
    char* query = (char*)setQuery(q);
    result = mysql_query(conn,query);

    return (result == 0) ? NULL : printf("No se ha podido realiar la consulta.. \n") ; // try ...
    
};

DatumType MdbDatabaseHandler::fetch(){
    
    DatumType result = 0;
    return result ;

};

DataType MdbDatabaseHandler::fetchAll(){
    DataType result = 0 ;
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



