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

int main()
{
    ComponentFactory* componentFactoryObject = new ComponentFactory();
    componentFactoryObject->setInterfaceName("DatabaseHandlerInterface");
    ComponentInterface* databaseHandlerComponent = componentFactoryObject->createFrom("../DatabaseHandler");
    DatabaseHandlerInterface* databaseHandlerObject = ( (DatabaseHandlerInterface*) databaseHandlerComponent->getInstance() );
    DataType allData = databaseHandlerObject->fetchAll();
    delete componentFactoryObject;

    return 0;
}