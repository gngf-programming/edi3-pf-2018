/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef APPLICATION_INTERFACE_H
#define APPLICATION_INTERFACE_H

#include <iostream>

class ApplicationInterface
{
    public:
    	virtual ~ApplicationInterface(){}
		virtual int run() = 0;
};

#endif // APPLICATION_INTERFACE_H
