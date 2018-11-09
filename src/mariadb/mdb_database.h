/********************************************************************************
* Copyright (c) 2018 Nano Nobile <crlsdnlnobile@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
*********************************************************************************/
#ifndef MDBDATABASE_H
#define MDBDATABASE_H

#include <iostream>

#include <fstream>
#include <string>

#include <compset/ComponentFactory.h>
#include <compset/ComponentInterface.h>
#include <compset/DatabaseHandlerInterface.h>

#include <mysql.h>

class MdbDatabaseHandler : public DatabaseHandlerInterfaz , public ComponentInterface {

        MdbDatabaseHandler() ;
        virtual ~MdbDatabaseHandler() ;
        virtual bool getErrorStatus() ;
        virtual DatabaseHandlerInterface * setQuery( std::string query ) ;
        virtual DatabaseHandlerInterface * setStoredProcedure( std::string storedProcedure ) ;
        virtual DatabaseHandlerInterface * addParameter( std::string key, std::string value ) ;
        virtual void execQuery() ;
        virtual DatumType fetch() ;
        virtual DataType fetchAll() ;

        bool implements( std::string interfaceName ) ; 
        void * getInstance() ;
        void release() ;

        private: 
        int referenceCounter;
        bool implemented;
        bool connected;

        MYSQL* conn;
        std::string data[5];
        const char* port;
        const char* user;
        const char* pass;
        const char* database;
        const char* host;
    
};

#endif // MDBDATABASE_H

