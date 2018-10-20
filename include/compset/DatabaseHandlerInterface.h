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


typedef std::vector< std::unordered_map<std::string, std::string> > DataType; 
typedef std::unordered_map<std::string, std::string> DatumType; 

class DatabaseHandler
{
    public:
    	virtual ~DatabaseHandler(){}
		virtual bool getErrorStatus() = 0;
		virtual bool getResultStatus() = 0;
		virtual DatabaseHandler* setQuery( std::string query ) = 0;
		virtual DatabaseHandler* setStoredProcedure( std::string storedProcedure ) = 0;
		virtual DatabaseHandler* withResultStatus() = 0;
		virtual DatabaseHandler* addParameter( std::string key, std::string value ) = 0;
		virtual void execQuery() = 0;
		virtual DataType fetch() = 0;
		virtual DatumType fetchAll() = 0;
		
		//virtual json execute();//En un futuro....
		//json
		//unordered_map<std::string, std::string> = 0;
		//virtual void dispose(); //Ver si realmente tiene que ser explícito 
};

#endif // DATABASE_HANLDER_INTERFACE_H