/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef REQUEST_HANDLER_INTERFACE_H
#define REQUEST_HANDLER_INTERFACE_H

#include <unordered_map>
#include <string>
#include <iostream>

class RequestHandlerInterface
{
    public:
        virtual ~RequestHandlerInterface() {}
    	virtual std::unordered_map<std::string, std::string> getRequestParameters() = 0;
};

#endif // REQUEST_HANDLER_INTERFACE_H