/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef RESPONSE_HANDLER_INTERFACE_H
#define RESPONSE_HANDLER_INTERFACE_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

typedef std::vector< std::unordered_map<std::string, std::string> > DataType; 

class ResponseHandlerInterface
{
    public:
        virtual ~ResponseHandlerInterface() {}
        virtual void setFormat(std::string format) = 0;
    	virtual void respond(DataType response) = 0;
};

#endif // RESPONSE_HANDLER_INTERFACE_H
