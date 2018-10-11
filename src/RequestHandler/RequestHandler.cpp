/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <compset/ComponentInterface.h>
#include <compset/RequestHandlerInterface.h>
 
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <regex>//FOR QUERY_STRING VALIDATION
#include <sstream>//FOR M_EXPLODE()
#include <cstdlib>//FOR GETEVENT()

typedef std::unordered_map<std::string, std::string> DatumType;

class RequestHandler : public RequestHandlerInterface, public ComponentInterface
{
    public:
        RequestHandler();
        virtual ~RequestHandler();

        //RequestHandler
        DatumType getRequestParameters();

        //ComponentInterface
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        std::string decode(std::string &input);
        std::vector<std::string> explode(std::string const &input, char delimiter);
        std::string getRequest();

        //ComponentInterface
        int referenceCounter;
        bool implemented;
};

RequestHandler::RequestHandler() : referenceCounter(0) {}

RequestHandler::~RequestHandler() {}

//Thanks Tominko...
std::string RequestHandler::decode(std::string &input)
{
    std::string ret;
    char ch;
    unsigned int i;
    unsigned int ii;
    
    for (i=0; i<input.length(); i++)
    {
        if (int(input[i])==37)
        {
            sscanf(input.substr(i+1,2).c_str(), "%x", &ii);
            ch=static_cast<char>(ii);
            ret+=ch;
            i=i+2;
        } else
        {
            ret+=input[i];
        }
    }
    return (ret);
}

std::vector<std::string> RequestHandler::explode(std::string const &input, char delimiter)
{
    std::vector<std::string> result;
    std::istringstream iss(input);

    for (std::string token; getline(iss, token, delimiter); )
    {
        result.push_back(move(token));
    }

    return result;
}

std::string RequestHandler::getRequest()
{
    std::string requestParametersString = "";

    if(getenv("REQUEST_METHOD") == NULL && getenv("TERMINAL_QUERY_STRING") == NULL)
    {
        std::cout << "The request method is null" << std::endl;
        exit(-1);
    }    
    if(getenv("REQUEST_METHOD") == NULL && getenv("TERMINAL_QUERY_STRING") != NULL)
    {
        std::string input = std::string(getenv("TERMINAL_QUERY_STRING"));
        bool isAQueryString = std::regex_match (input , std::regex("^([^=]+=[^=]+&)+[^=]+(=[^=]+)?$"));
        
        if (isAQueryString)
        {
            requestParametersString = input;
        }
        else
        {
            std::cout << "The request is not a QUERY_STRING" << std::endl;
            exit(-1);
        } 
    }
    else
    {
        std::string request_method = std::string(getenv("REQUEST_METHOD"));

        if(request_method == "GET") { requestParametersString = std::string(getenv("QUERY_STRING")); }

        if(request_method == "POST") { std::cin >> requestParametersString; }
    }

    return requestParametersString;
}

DatumType RequestHandler::getRequestParameters()
{
    std::string requestParametersString = this->getRequest();
    std::vector<std::string> keysWithValues = explode( decode(requestParametersString), '&' );
    std::vector<std::string> keysAndValues;
    std::vector<std::string>::iterator i;

    int aux = 0;
    DatumType requestParametersMap;

    for(i = keysWithValues.begin(); i != keysWithValues.end(); i++)
    {
        keysAndValues = explode( keysWithValues[aux], '=' );
        requestParametersMap[keysAndValues[0]] = keysAndValues[1];
        aux++;
    }

    return requestParametersMap;
}

/********************************************************************************************/
/*COMPONENT SECTION INTERFACE*/
bool RequestHandler::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "RequestHandlerInterface") ?
        implemented = true
            : implemented = false;
}

void* RequestHandler::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void RequestHandler::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new RequestHandler;
}
