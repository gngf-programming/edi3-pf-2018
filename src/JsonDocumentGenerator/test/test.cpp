/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

#include <compset/ComponentFactory.h>
#include <compset/ComponentInterface.h>
#include <compset/DocumentGeneratorInterface.h>

typedef std::vector< std::unordered_map<std::string, std::string> > DataType; 
typedef std::unordered_map<std::string, std::string> DatumType; 

int main()
{
    DataType data;
    DatumType datum;

    datum["last_name"] = "Doe";
    datum["first_name"] = "John";
    data.push_back(datum);

    datum["last_name"] = "Smith";
    datum["first_name"] = "Ana";
    data.push_back(datum);
    
    datum["last_name"] = "Jones";
    datum["first_name"] = "Peter";
    data.push_back(datum);

    ComponentFactory* componentFactoryObject = new ComponentFactory();
    componentFactoryObject->setInterfaceName("DocumentGeneratorInterface");
    ComponentInterface* documentGeneratorComponent = componentFactoryObject->createFrom("../JsonDocumentGenerator");
    delete componentFactoryObject;

    DocumentGeneratorInterface* documentGeneratorObject = ( (DocumentGeneratorInterface*) documentGeneratorComponent->getInstance() );
    documentGeneratorObject->setContent(data);
    std::cout << "Test Document: " << documentGeneratorObject->getDocument() << std::endl;
    documentGeneratorComponent->release();
    return 0;
}
