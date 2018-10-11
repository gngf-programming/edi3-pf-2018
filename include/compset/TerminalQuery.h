/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#ifndef TERMINAL_QUERY_H
#define TERMINAL_QUERY_H

#include <compset/LibraryLoader.h>
#include <cstring>

void setTerminalQuery(const char* value)
{
    LibraryLoader* loaderObject = LibraryLoader::getInstance();
    loaderObject->loadLibrary("./lib/PortableEnviromentVariable");
    typedef int (*FUNC_TYPE)(const char*, const char*, int);
    FUNC_TYPE portableSetEnvFunction = ( FUNC_TYPE ) loaderObject->getExternalFunction( "portableSetEnv" );
    portableSetEnvFunction("TERMINAL_QUERY_STRING", value, 0);
    loaderObject->freeLibrary();
}

#endif // TERMINAL_QUERY_H