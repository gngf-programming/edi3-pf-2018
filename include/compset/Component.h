/**
* Copyright (c) 2018 Giuliano Decesares <giulianodecesares@gmail.com>. All rights reserved. 
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#pragma once

#include "ComponentInterface.h"
#include "ComponentFactory.h"

#include <assert.h>

/*

This is the creation of a component class to abstract the complexity of the components 
and isolate all its dependencies ("ComponentInterface.h" & "ComponentFactory.h")

This object encapsulates the complexity of the component. Otherwise, in the main you have to keep two pointers:
one of the component itself to free its memory space, and the other that of the object, for its use (duh).

The user only needs the object, and does not have to know that he needs to keep a pointer 
to the component interface to make the memory release and other component-related stuff.

i. e. I need to use a XML document creator, I don't care if it's a component. All component-related complexity it's not of my bussines.

*/

#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

template< typename Interface >
class Component
{
private:
	ComponentInterface* component;
	Interface* object;

	Component(const Component&) {}
	Component(const Component&&) {}

	Component<Interface>& operator =(const Component<Interface>&) { return *this; }

	// Private default constructor to avoid bad initialization case
	Component(void) : component(nullptr), object(nullptr) {}

	// Helper methods
	ComponentInterface* _createComponent(std::string interfaceName, std::string createFromDirectory)
	{
		ComponentInterface* component = nullptr;

		ComponentFactory* factory = new ComponentFactory();
		factory->setInterfaceName(interfaceName);

		component = factory->createFrom(createFromDirectory);
		delete factory;

		return component;
	}

	Interface* _createObject(ComponentInterface* component)
	{
		Interface* object = nullptr;

		object = ((Interface*)component->getInstance());

		return object;
	}

public:
	Component(std::string interfaceName, std::string createFromDirectory)
	{
		assert(interfaceName != "");
		assert(createFromDirectory != "");

		this->component = this->_createComponent(interfaceName, createFromDirectory);

		assert(this->component != nullptr);

		this->object = this->_createObject(this->component);
	}

	~Component(void)
	{
		if (this->component != nullptr)
		{
			this->component->release();
		}

		/*

		if (this->object != nullptr)
		{
			delete this->object;
		}

		*/		
	}

	Interface* operator ->()
	{
		return this->object;
	}
};

#endif // !COMPONENT_H_INCLUDED
