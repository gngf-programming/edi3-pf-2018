/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <compset/TerminalQuery.h>
#include <compset/ComponentFactory.h>
#include <compset/ComponentInterface.h>
#include <compset/ApplicationInterface.h>

int main(int argc, char* argv[])
{
    if ( 1 < argc ) setTerminalQuery(argv[1]);

    ComponentFactory* componentFactoryObject = new ComponentFactory();
    componentFactoryObject->setInterfaceName("ApplicationInterface");
    ComponentInterface* applicationComponent = componentFactoryObject->createFrom("./lib/Application");
    delete componentFactoryObject;

    ApplicationInterface* applicationObject = ( (ApplicationInterface*) applicationComponent->getInstance() );
    applicationObject->run();
    applicationComponent->release();

    return 0;
}