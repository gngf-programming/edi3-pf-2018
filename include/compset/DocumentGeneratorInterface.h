/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef DOCUMENT_GENERATOR_INTERFACE_H
#define DOCUMENT_GENERATOR_INTERFACE_H

#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>

typedef std::vector< std::unordered_map<std::string, std::string> > DataType; 

class DocumentGeneratorInterface
{
    public:
        virtual ~DocumentGeneratorInterface() {}
        
    	virtual void setContent(DataType content) = 0;
    	virtual std::string getDocument() = 0;
};

#endif // DOCUMENT_GENERATOR_INTERFACE_H