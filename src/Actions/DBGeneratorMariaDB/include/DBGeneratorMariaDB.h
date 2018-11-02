#ifndef __DB_GENERATOR__
#define __DB_GENERATOR__

#include <windows.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <mysql.h>
#include <ComponentInterface.h>
#include <ActionInterface.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DB_GENERATOR __declspec(dllexport)
#else
    #define DB_GENERATOR __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

class DBGeneratorMariaDB : public ActionInterface, public ComponentInterface
{
    public:
        DBGeneratorMariaDB();
        virtual ~DBGeneratorMariaDB();
        int execute();

        //ComponentInterface
        bool implements(std::string interfaceName);
        void* getInstance();
        void release();

    private:
        const char* MY_HOSTNAME;
        const char* MY_DATABASE;
        const char* MY_USERNAME;
        const char* MY_PASSWORD;
        const char* MY_SOCKET;
        enum {
            MY_PORT_NO = 3306,
            MY_OPT     = 0
        };
        MYSQL     *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;
        //ComponentInterface
        int referenceCounter;
        bool implemented;
};



#ifdef __cplusplus
}
#endif

#endif // __DB_GENERATOR_
