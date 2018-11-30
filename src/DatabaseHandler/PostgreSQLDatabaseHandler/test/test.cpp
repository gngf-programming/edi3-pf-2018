/**
* Copyright (c) 2018 Leonardo Casales <leonardo@smartnet.com.ar> - Jonathan Egea. All rights reserved.
* Released under the MIT license
**/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include <compset/ComponentInterface.h>
#include <compset/ComponentFactory.h>
#include <compset/DatabaseHandlerInterface.h>

int main()
{
    ComponentFactory* componentFactoryObject = new ComponentFactory();
    componentFactoryObject->setInterfaceName("DatabaseHandlerInterface");
    ComponentInterface* databaseHandlerComponent = componentFactoryObject->createFrom("../PostgreSQLDatabaseHandler");
    DatabaseHandlerInterface* databaseHandlerObject = ( (DatabaseHandlerInterface*) databaseHandlerComponent->getInstance() );
    databaseHandlerObject->prepareQuery( "SELECT * FROM USERS WHERE identifier = $1" ) ;
    databaseHandlerObject->addParameter( 1, "leo") ;
    Row firstRow = databaseHandlerObject->fetch() ;

    for (std::pair<std::string, std::string> element : firstRow )
    {
        std::cout << element.first << " :: " << element.second << std::endl ;
    }

    delete componentFactoryObject;

    return 0;
}