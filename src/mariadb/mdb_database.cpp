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

void MdbDatabaseHandler::prepareQuery(std::string query){
    
    setQuery = query ;
    
};



void MdbDatabaseHandler::addParameter(std::string key, std::string value){

    return null;

};

void MdbDatabaseHandler::execute() {
    
    unsigned int result = 0;
    result = mysql_query(conn,setQuery.c_str());

    return (result == 0) ? NULL : printf("No se ha podido realiar la consulta.. \n") ; // try ...
    
};

Row MdbDatabaseHandler::fetch(){
    
    Row result = 0;
    return result ;

};

Table MdbDatabaseHandler::fetchAll(){
    Table result = 0 ;
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



