/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include <compset/ComponentInterface.h>
#include <compset/ComponentFactory.h>
#include <compset/DatabaseHandlerInterface.h>

// typedef std::unordered_map< std::string, std::string > Row; 
// typedef std::vector< Row > Table; 

int main()
{
    ComponentFactory* componentFactoryObject = new ComponentFactory();
    componentFactoryObject->setInterfaceName("DatabaseHandlerInterface");
    ComponentInterface* databaseHandlerComponent = componentFactoryObject->createFrom("../PosgreSQLDatabaseHandler");
    DatabaseHandlerInterface* databaseHandlerObject = ( (DatabaseHandlerInterface*) databaseHandlerComponent->getInstance() );
    databaseHandlerObject->prepareQuery( "SELECT * FROM users" ) ; // WHERE %i = %j" ) ;
    databaseHandlerObject->addParameter( 0, "gabi") ;
    databaseHandlerObject->execute() ;
    Row firstRow = databaseHandlerObject->fetch() ;

    // Row::iterator it = firstRow.begin() ;
 
    // // Iterate over the map using iterator
    // while(it != firstRow.end())
    // {
    //     std::cout << it->first << " :: " << it->second << std::endl ;
    //     it++;
    // }
    // Iterate over an unordered_map using range based for loop

    for (std::pair<std::string, std::string> element : firstRow )
    {
        std::cout << element.first << " :: " << element.second << std::endl ;
    }

    // for ( firstRow.begin() firstRow.count() ; i++) {
    //     std::cout << "ID: " << firstRow["id"] << std::endl ;

    //     std::cout << "IDENTIFIER: " << firstRow["identifier"] << std::endl ;

    //     std::cout << "PASSWORD: " << firstRow["password_hash"] << std::endl ;
    // }

    delete componentFactoryObject;

    return 0;
}