/**
* Copyright (c) 2016 Gabriel Ferreira <gabrielinuz@gmail.com>. All rights reserved. 
* This file is part of COMPSET.
* Released under the GPL3 license
* https://opensource.org/licenses/GPL-3.0
**/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int portableSetEnv(const char* name, const char* value, int overwrite)
{
    int result;
    #ifdef __unix__
        result = setenv(name, value, overwrite);
    #elif defined(_WIN32) || defined(WIN32)
        char env[1024];
        strcpy( env, name );
        strcat( env, "=" );
        strcat( env, value );
        /*ToDo: */
        // if(!overwrite) 
        // {
            // size_t envsize = 0;
            // errcode = getenv(envsize, NULL, 0, name);
            // if(errcode || envsize) return errcode;
        // }
        result = putenv(env);
    #endif // defined
    return result;
}