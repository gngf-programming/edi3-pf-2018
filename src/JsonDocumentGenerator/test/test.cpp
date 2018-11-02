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
#include <algorithm>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>

#include <compset/ComponentFactory.h>
#include <compset/ComponentInterface.h>
#include <compset/DocumentGeneratorInterface.h>

typedef std::vector< std::unordered_map<std::string, std::string> > DataType;
typedef std::unordered_map<std::string, std::string> DatumType;

bool IsErasableCharacter(char c)
{
    switch(c)
    {
        case '\n':
        case '\t':
        case ' ':
        case '"':
            return true;
        default:
            return false;
    }
}

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

    ComponentFactory* componentFactoryObject = new ComponentFactory();
    componentFactoryObject->setInterfaceName("DocumentGeneratorInterface");
    ComponentInterface* documentGeneratorComponent = componentFactoryObject->createFrom("../JsonDocumentGenerator");
    delete componentFactoryObject;

    DocumentGeneratorInterface* documentGeneratorObject = ( (DocumentGeneratorInterface*) documentGeneratorComponent->getInstance() );
    documentGeneratorObject->setContent(data);
    std::string str1 = documentGeneratorObject->getDocument();
    str1.erase(std::remove_if(str1.begin(), str1.end(), &IsErasableCharacter), str1.end());
    documentGeneratorComponent->release();

    std::string str2 = "Content-type:Application/json;charset=utf-8{data:[{first_name:John,last_name:Doe},{first_name:Ana,last_name:Smith}]}";

    std::cout << std::endl;
    std::cout << "Obtained Document: " << str1 << std::endl << std::endl;
    std::cout << "Expected Document: " << str2 << std::endl << std::endl;

    assert((str2 == str1));
    std::cout << "The JSON document results are equals" << std::endl << std::endl;    

    return 0;
}
