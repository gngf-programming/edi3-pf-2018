/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <iostream>
#include <cstring>
#include <compset/LibraryLoader.h>

int main()
{
    LibraryLoader* loaderObject = LibraryLoader::getInstance();
    void* load = loaderObject->loadLibrary("../PortableEnviromentVariable");
 
    if(load)
    {   
        typedef int (*FUNC_TYPE)(const char*, const char*, int);
        FUNC_TYPE portableSetEnvFunction = ( FUNC_TYPE ) loaderObject->getExternalFunction( "portableSetEnv" );
        if (portableSetEnvFunction)
        {
            portableSetEnvFunction("TERMINAL_QUERY_STRING", "action=TestRequestResponse&greeting=Hello", 0);
            std::cout << "TESTING-OK: " << getenv("TERMINAL_QUERY_STRING") << std::endl;
        }
        else
        {
            std::cout << "NOT FUNCTION" << std::endl;
        }
    }
    else
    {
        std::cout << "NOT LOAD" << std::endl;
    }

    loaderObject->freeLibrary();
    std::cout << "END" << std::endl;
    return 0;
}
