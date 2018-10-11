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
#include <compset/RequestHandlerInterface.h>

typedef std::vector< std::unordered_map<std::string, std::string> > DataType; 
typedef std::unordered_map<std::string, std::string> DatumType; 


int main()
{
    DataType data;
    DatumType datum;

    ComponentFactory* componentFactoryObject = new ComponentFactory();

    componentFactoryObject->setInterfaceName("RequestHandlerInterface");
    ComponentInterface* requestHandlerComponent = componentFactoryObject->createFrom("../RequestHandler");
    RequestHandlerInterface* requestHandlerObject = ( (RequestHandlerInterface*) requestHandlerComponent->getInstance() );
    DatumType requestParameters = requestHandlerObject->getRequestParameters();
    data.push_back(requestParameters);
    requestHandlerComponent->release();
    
    delete componentFactoryObject;

    std::cout << requestParameters["action"] << std::endl;
    std::cout << "RESULT:" << std::endl;
    std::cout << "\t\tTEST OK!!!!!" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;

    return 0;
}