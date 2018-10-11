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

typedef std::vector< std::unordered_map<std::string, std::string> > DataType; 
typedef std::unordered_map<std::string, std::string> DatumType; 

class TestRequestResponse : public ActionInterface, public ComponentInterface
{
    public:
        TestRequestResponse();
        virtual ~TestRequestResponse();
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

TestRequestResponse::TestRequestResponse() : referenceCounter(0){}

TestRequestResponse::~TestRequestResponse(){}

int TestRequestResponse::execute()
{
    ComponentFactory* componentFactoryObject = new ComponentFactory();

    componentFactoryObject->setInterfaceName("RequestHandlerInterface");
    ComponentInterface* requestHandlerComponent = componentFactoryObject->createFrom("./lib/RequestHandler");
    RequestHandlerInterface* requestHandlerObject = ( (RequestHandlerInterface*) requestHandlerComponent->getInstance() );
    DatumType requestParameters = requestHandlerObject->getRequestParameters();
    DataType data;
    data.push_back(requestParameters);
    requestHandlerComponent->release();

    componentFactoryObject->setInterfaceName("ResponseHandlerInterface");
    ComponentInterface* responseHandlerComponent = componentFactoryObject->createFrom("./lib/ResponseHandler");
    ResponseHandlerInterface* responseHandlerObject = ( (ResponseHandlerInterface*) responseHandlerComponent->getInstance() );
    responseHandlerObject->respond(data);   
    responseHandlerComponent->release();
    
    delete componentFactoryObject;

    return 0;
}

/********************************************************************************************/
/*COMPONENT SECTION INTERFACE*/
bool TestRequestResponse::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "ActionInterface") ?
        implemented = true
            : implemented = false;
}

void* TestRequestResponse::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void TestRequestResponse::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new TestRequestResponse;
}
