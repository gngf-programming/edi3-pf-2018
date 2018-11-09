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

typedef std::unordered_map< std::string, std::string > Row; 
typedef std::vector< Row > Table; 

class DatabaseHandlerInterface
{
    public:
        virtual ~DatabaseHandlerInterface(){}
        virtual bool getErrorStatus() = 0;
        virtual void prepareQuery( std::string query ) = 0;
        // virtual void addParameter( std::string key, std::string value ) = 0;
        virtual void addParameter( int key, std::string value ) = 0;
        virtual void execute() = 0;
        virtual Row fetch() = 0;
        virtual Table fetchAll() = 0;
};

#endif // DATABASE_HANLDER_INTERFACE_H