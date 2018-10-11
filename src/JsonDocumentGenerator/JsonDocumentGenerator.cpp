/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <vector>
#include <unordered_map>
#include <string>
#include <typeinfo>
#include <iostream>

#include <compset/ComponentInterface.h>
#include <compset/DocumentGeneratorInterface.h>

typedef std::vector< std::unordered_map<std::string, std::string> > DataType; 
typedef std::unordered_map<std::string, std::string> DatumType; 

class JsonDocumentGenerator : public DocumentGeneratorInterface, public ComponentInterface
{
    public:
        JsonDocumentGenerator();
        virtual ~JsonDocumentGenerator();

        //DocumentGeneratorInterface
        void setContent(DataType content);
        std::string getDocument();

        //ComponentInterface
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        //JsonDocumentGenerator
        std::string document;
        std::string stringReplace(std::string search, std::string replace, std::string subject);
        std::string parseContent(DataType content);

        //ComponentInterface
        int referenceCounter;
        bool implemented;
};

JsonDocumentGenerator::JsonDocumentGenerator() : referenceCounter(0){}

JsonDocumentGenerator::~JsonDocumentGenerator(){}

std::string JsonDocumentGenerator::stringReplace(std::string search, std::string replace, std::string subject)
{
    while(subject.find(search) != std::string::npos)
    {
       subject.replace(subject.find(search), search.size(), replace);
    }
    return subject;
}

std::string JsonDocumentGenerator::parseContent(DataType content)
{
    DataType::iterator dataI;
    DatumType::iterator datumI;
    std::string parsedContent;

    for(dataI = content.begin(); dataI != content.end(); dataI++)
    {
        parsedContent += "{";
        for(datumI = (*dataI).begin(); datumI != (*dataI).end(); datumI++)
        {
            parsedContent += "\""+datumI->first+"\": \""+datumI->second+"\"";
        }
        parsedContent += "}";
    }
    
    parsedContent = stringReplace("\"\"", "\", \"", parsedContent);
    parsedContent = stringReplace("}{", "}, \n\t{", parsedContent);
    parsedContent = stringReplace(": \", \"", ": null", parsedContent);
    parsedContent = stringReplace("\": null\"", "\": null, \"", parsedContent);

    return parsedContent;
}

void JsonDocumentGenerator::setContent(DataType content)
{
    document += "Content-type: Application/json; charset=utf-8\n\n";
    document += "{\"data\":[\n\t";
    document += parseContent(content);
    document += "\n]}";
}

std::string JsonDocumentGenerator::getDocument()
{
    return document;
}

/********************************************************************************************/
/*COMPONENT SECTION INTERFACE*/
bool JsonDocumentGenerator::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "DocumentGeneratorInterface") ?
        implemented = true
            : implemented = false;
}

void* JsonDocumentGenerator::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void JsonDocumentGenerator::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new JsonDocumentGenerator;
}
