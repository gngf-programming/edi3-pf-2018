/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef COPONENT_FACTORY_H
#define COPONENT_FACTORY_H

#include <iostream>
#include <stdlib.h>
#include <string>
#include "LibraryLoader.h"
#include "ComponentInterface.h"

class ComponentFactory
{
    public:
        ComponentFactory();
        ComponentFactory(std::string interfaceName);
 		void setInterfaceName(std::string interfaceName);
        virtual ~ComponentFactory();
        ComponentInterface* createFrom(std::string path);

    private:
    	std::string interfaceName;
};

ComponentFactory::ComponentFactory()
{
    //ctor
    this->interfaceName = "";
}

ComponentFactory::~ComponentFactory()
{
    //dtor
}

ComponentFactory::ComponentFactory(std::string interfaceName)
{
    this->interfaceName = interfaceName;
}

void ComponentFactory::setInterfaceName(std::string interfaceName)
{
    this->interfaceName = interfaceName;
}

ComponentInterface* ComponentFactory::createFrom(std::string path)
{
    ComponentInterface* componentObject = NULL;
    bool notNullFactory; 

    //THE LOADER:
    LibraryLoader* loaderObject = LibraryLoader::getInstance();

    //LOAD
    void* load = loaderObject->loadLibrary(path);

    if(load)
    {
        typedef ComponentInterface* ( *ComponentFactory ) ();
        ComponentFactory factory = ( ComponentFactory ) loaderObject->getExternalFunction( "create" );

        if ( factory )
        {
            ComponentInterface* createdComponent;
            notNullFactory = (createdComponent = factory());

            if ( notNullFactory )            
            {
                if(this->interfaceName != "")
                {
                    if(createdComponent->implements(this->interfaceName))
                    {
                        componentObject = createdComponent;
                    }
                    else
                    {
                        std::cout << "Error: The component doesn't implement the "+this->interfaceName+" interface!" << std::endl;
                        exit(-1);
                    }
                }
                else
                {
                    std::cout << "Error: The component requires an interface!" << std::endl;
                    exit(-1);
                }
            }
            else
            {
                loaderObject->freeLibrary();
                std::cout << "Error:  Failed creating a component from "
                        << path << ", null component." << std::endl;
                exit(-1);
            }

        }
        else
        {
            loaderObject->freeLibrary();
            std::cout << "Error:  Failed creating a component from "
                    << path << ", there is no external function \"create(void)\"." << std::endl;
            exit(-1);
        }
    }
    else
    {
        std::cout << "Error: Failed to load the component: " << path << std::endl;
        exit(-1);
    }

    return componentObject;
}

#endif // COPONENT_FACTORY_H