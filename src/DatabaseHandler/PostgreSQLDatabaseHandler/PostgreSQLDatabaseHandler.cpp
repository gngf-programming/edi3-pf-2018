/**
* Copyright (c) 2018 Leonardo Casales <leonardo@smartnet.com.ar> - Jonathan Egea. All rights reserved.
* Released under the MIT license
**/
#include "libpq-fe.h"

#include <iostream>
#include <string>
#include <fstream>

#include <compset/ComponentFactory.h>

#include <compset/DatabaseHandlerInterface.h>
#include <compset/ComponentInterface.h>

typedef std::unordered_map< std::string, std::string > Row; 
typedef std::vector< Row > Table; 

class PostgeSQLDatabaseHandler : public DatabaseHandlerInterface, public ComponentInterface {

    public:
        PostgeSQLDatabaseHandler() ;
        virtual ~PostgeSQLDatabaseHandler() ;
        virtual bool getErrorStatus() ;
        virtual void prepareQuery( std::string query ) ;
        virtual void addParameter( int key, std::string value ) ;
        virtual void execute() ;
        virtual Row fetch() ;
        virtual Table fetchAll() ;

        //ComponentInterface:
        bool implements(std::string interfaceName);
        void* getInstance() ;
        void release() ;

    private:
        std::string host ;
        std::string dataBase ;
        std::string port ;
        std::string user ;
        std::string passwd ;
        bool isError ;
        PGconn* cnn ;
        PGresult* result ;
        bool connected ;
        std::string qSQL ;
        void ReadConfig() ;

        int referenceCounter ;
        bool implemented ;
};

PostgeSQLDatabaseHandler::PostgeSQLDatabaseHandler () {
    ReadConfig() ;

    cnn = NULL ;
    result = NULL ;
    qSQL = "" ;
	cnn = PQsetdbLogin( host.c_str() ,
                        port.c_str() , NULL , NULL ,
                        dataBase.c_str() , 
                        user.c_str() ,
                        passwd.c_str() );
                        
    if (PQstatus(cnn) != CONNECTION_BAD) {
        connected = true ;
        result = PQexec(cnn, "");
        isError = false ;
	} else {
		PQfinish( cnn ) ;
		connected = false ;
        isError = true ;
	}
}

PostgeSQLDatabaseHandler::~PostgeSQLDatabaseHandler() {
	if ( connected ) {
    	PQclear( result ) ;
    	PQfinish( cnn ) ;
	}
}

void PostgeSQLDatabaseHandler::prepareQuery( std::string query ) {
    qSQL = query ;
}

void PostgeSQLDatabaseHandler::addParameter( int key, std::string value ) {
    const char *paramValues[1];
    
    paramValues[0] = value.c_str() ;
    
    result = PQexecParams( cnn, qSQL.c_str(), key, NULL, paramValues, NULL, NULL, 0 ) ;
    // std::cout<< "parametro " << value << std::endl ;
    if ( PQresultStatus( result ) != PGRES_TUPLES_OK )
    {
        isError = true ;
        // fprintf(stderr, "SELECT failed: %s", PQerrorMessage(conn));
        PQclear(result);
        // exit_nicely(conn);
    }
}

void PostgeSQLDatabaseHandler::ReadConfig() {
	std::ifstream file;
	std::string text[10];

	file.open("config.txt", std::ios::in);

	if (file.fail()) {
		std::cout << "no se reconoce archivo de configuración";
	}
	int i=0;
	while( !file.eof() ) {
        getline( file, text[i] );
        // std::cout << text[i] << std::endl ;
        i++ ;
    }
    dataBase = text[0] ;
    host = text[1] ;
    port = text[2] ;
    user = text[3] ;
    passwd = text[4] ;
}

void PostgeSQLDatabaseHandler::execute() {
    
    if ( connected ) {
        PQclear( result );
        result = PQexec( cnn , qSQL.c_str() ) ;
        if ( result != NULL ) {
            isError = false ;
            // printf( "%s\n", PQerrorMessage( cnn ));
        } else {
            isError = true ;
            // printf( "%s\n", PQerrorMessage( cnn ));
        }
    }
}

bool PostgeSQLDatabaseHandler::getErrorStatus() {
    return isError ;
}

Row PostgeSQLDatabaseHandler::fetch() {
    Row row ;
    int columnCount = PQnfields(result);
    for ( int i = 0 ; i < columnCount ; i++ ) {
        std::string columnName = std::string( PQfname( result, i ) );
        std::string columnValue = std::string( PQgetvalue( result , 0 , i ) );
        row[columnName] = columnValue;    
    }
    return row; 
}

Table PostgeSQLDatabaseHandler::fetchAll() {
    Table result ;
    return result ;
}

//ComponentInterface:
bool PostgeSQLDatabaseHandler::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "DatabaseHandlerInterface") ?
        implemented = true
            : implemented = false;
}

void* PostgeSQLDatabaseHandler::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void PostgeSQLDatabaseHandler::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new PostgeSQLDatabaseHandler;
}
