/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <unordered_map>
#include <string>

#include <compset/ComponentInterface.h>
#include <compset/ComponentFactory.h>
#include <compset/RequestHandlerInterface.h>
#include <compset/ResponseHandlerInterface.h>
#include <compset/ActionInterface.h>

#include <libpq++.h>

typedef std::vector< std::unordered_map<std::string, std::string> > DataType; 
typedef std::unordered_map<std::string, std::string> DatumType; 

class DBGeneratorPostgre : public ActionInterface, public ComponentInterface
{
    public:
        DBGeneratorPostgre();
        virtual ~DBGeneratorPostgre();
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

DBGeneratorPostgre::DBGeneratorPostgre() : referenceCounter(0){}

DBGeneratorPostgre::~DBGeneratorPostgre(){}

int DBGeneratorPostgre::execute()
{
    
    return 0;
}

/********************************************************************************************/
/*COMPONENT SECTION INTERFACE*/
bool DBGeneratorPostgre::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "ActionInterface") ?
        implemented = true
            : implemented = false;
}

void* DBGeneratorPostgre::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void DBGeneratorPostgre::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new DBGeneratorPostgre;
}
