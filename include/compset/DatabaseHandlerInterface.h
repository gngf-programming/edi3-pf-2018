/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef DATABASE_HANLDER_INTERFACE_H
#define DATABASE_HANLDER_INTERFACE_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

typedef std::unordered_map< std::string, std::string > DatumType; 
typedef std::vector< DatumType > DataType; 

class DatabaseHandlerInterface
{
    public:
        virtual ~DatabaseHandlerInterface(){}
        virtual bool getErrorStatus() = 0;
        virtual DatabaseHandlerInterface* setQuery( std::string query ) = 0;
        virtual DatabaseHandlerInterface* setStoredProcedure( std::string storedProcedure ) = 0;
        virtual DatabaseHandlerInterface* addParameter( std::string key, std::string value ) = 0;
        virtual void execQuery() = 0;
        virtual DatumType fetch() = 0;
        virtual DataType fetchAll() = 0;
        //virtual void dispose(); //Ver si realmente tiene que ser explícito 
};

#endif // DATABASE_HANLDER_INTERFACE_H