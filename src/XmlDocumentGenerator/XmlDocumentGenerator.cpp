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

class XmlDocumentGenerator : public DocumentGeneratorInterface, public ComponentInterface
{
    public:
        XmlDocumentGenerator();
        virtual ~XmlDocumentGenerator();

        //DocumentGeneratorInterface
        void setContent(DataType content);
        std::string getDocument();

        //ComponentInterface
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        //XmlDocumentGenerator
        std::string document;
        std::string parseContent(DataType content);

        //ComponentInterface
        int referenceCounter;
        bool implemented;
};

XmlDocumentGenerator::XmlDocumentGenerator() : referenceCounter(0){}

XmlDocumentGenerator::~XmlDocumentGenerator(){}

std::string XmlDocumentGenerator::parseContent(DataType content)
{
    DataType::iterator dataI;
    DatumType::iterator datumI;
    std::string parsedContent;

    for(dataI = content.begin(); dataI != content.end(); dataI++)
    {
        parsedContent += "\n\t<datum>";
        for(datumI = (*dataI).begin(); datumI != (*dataI).end(); datumI++)
        {
            parsedContent += "\n\t\t<"+datumI->first+">"+datumI->second+"<"+datumI->first+">";
        }
        parsedContent += "\n\t</datum>";
    }
    
    return parsedContent;
}

void XmlDocumentGenerator::setContent(DataType content)
{
    document += "Content-type: text/xml; charset=utf-8\n\n";
    document += "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    document += "<data>";
    document += parseContent(content);
    document += "\n</data>";
}

std::string XmlDocumentGenerator::getDocument()
{
    return document;
}

/********************************************************************************************/
/*COMPONENT SECTION INTERFACE*/
bool XmlDocumentGenerator::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "DocumentGeneratorInterface") ?
        implemented = true
            : implemented = false;
}

void* XmlDocumentGenerator::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void XmlDocumentGenerator::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new XmlDocumentGenerator;
}
