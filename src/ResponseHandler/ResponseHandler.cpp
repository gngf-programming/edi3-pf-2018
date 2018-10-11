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

#include <compset/ComponentInterface.h>
#include <compset/ComponentFactory.h>
#include <compset/ResponseHandlerInterface.h>
#include <compset/DocumentGeneratorInterface.h>

typedef std::vector< std::unordered_map<std::string, std::string> > DataType; 

class ResponseHandler : public ResponseHandlerInterface, public ComponentInterface
{
    public:
        ResponseHandler();
        virtual ~ResponseHandler();

        //ResponseHandlerInterface
        void setFormat(std::string format);
        void respond(DataType response);

        //ComponentInterface
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        //ResponseHandler
        std::string format;

        //ComponentInterface
        int referenceCounter;
        bool implemented;
};

ResponseHandler::ResponseHandler() : referenceCounter(0) 
{
    this->format = "";
}

ResponseHandler::~ResponseHandler() {}

void ResponseHandler::setFormat(std::string format)
{
    this->format = format;
}

void ResponseHandler::respond(DataType response)
{
    ComponentFactory* componentFactoryObject = new ComponentFactory();
    componentFactoryObject->setInterfaceName("DocumentGeneratorInterface");
    ComponentInterface* documentGeneratorComponent;
    bool haveFormat = !(this->format == "");
    if ( !haveFormat ) documentGeneratorComponent = componentFactoryObject->createFrom("./lib/JsonDocumentGenerator");
    if ( haveFormat ) documentGeneratorComponent = componentFactoryObject->createFrom("./lib/"+this->format+"DocumentGenerator");
    
    delete componentFactoryObject;

    DocumentGeneratorInterface* documentGeneratorObject = ( (DocumentGeneratorInterface*) documentGeneratorComponent->getInstance() );
    documentGeneratorObject->setContent(response);
    std::cout << documentGeneratorObject->getDocument() << std::endl;
    documentGeneratorComponent->release();
}

/********************************************************************************************/
/*COMPONENT SECTION INTERFACE*/
bool ResponseHandler::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "ResponseHandlerInterface") ?
        implemented = true
            : implemented = false;
}

void* ResponseHandler::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void ResponseHandler::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new ResponseHandler;
}
