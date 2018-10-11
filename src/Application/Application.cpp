/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <cmath>

#include <unordered_map>
#include <string>

#include <compset/ComponentFactory.h>

#include <compset/ApplicationInterface.h>
#include <compset/ComponentInterface.h>
#include <compset/RequestHandlerInterface.h>
#include <compset/ActionInterface.h>

typedef std::unordered_map<std::string, std::string> DatumType; 

class Application : public ApplicationInterface, public ComponentInterface
{
    public:
        Application();
        virtual ~Application();
        int run();

        //ComponentInterface
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        //ComponentInterface
        int referenceCounter;
        bool implemented;
};

Application::Application() : referenceCounter(0){}

Application::~Application(){}

int Application::run()
{
    ComponentFactory* componentFactoryObject = new ComponentFactory();

    componentFactoryObject->setInterfaceName("RequestHandlerInterface");
    ComponentInterface* requestHandlerComponent = componentFactoryObject->createFrom("./lib/RequestHandler");
    RequestHandlerInterface* requestHandlerObject = ( (RequestHandlerInterface*) requestHandlerComponent->getInstance() );
    DatumType requestParameters = requestHandlerObject->getRequestParameters();
    requestHandlerComponent->release();

    componentFactoryObject->setInterfaceName("ActionInterface");
    ComponentInterface* actionComponent = componentFactoryObject->createFrom("./lib/Actions/" + requestParameters["action"]);
    ActionInterface* actionObject = ( (ActionInterface*) actionComponent->getInstance() );
    actionObject->execute();
    actionComponent->release();
    
    delete componentFactoryObject;
    
    return 0;
}

//ComponentInterface
bool Application::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "ApplicationInterface") ?
        implemented = true
            : implemented = false;
}

void* Application::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void Application::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new Application;
}
