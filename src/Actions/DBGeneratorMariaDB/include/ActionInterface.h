/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef ACTION_INTERFACE_H
#define ACTION_INTERFACE_H

#include <iostream>

class ActionInterface
{
    public:
    	virtual ~ActionInterface(){}
		virtual int execute() = 0;
};

#endif // ACTION_INTERFACE_H