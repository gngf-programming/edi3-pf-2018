/**
* Copyright (c) 2018 Leonardo Casales - Jonathan Egea. All rights reserved. .0
**/

// #include <libpq-fe.h> // include\vendors\postgreSQL\libpq-fe.h
// #include "/Library/PostgreSQL/11/include/libpq-fe.h"
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
        const char* host ;
        const char* dataBase ;
        const char* port ;
        const char* user ;
        const char* passwd ;
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
    // ReadConfig() ;

    cnn = NULL ;
    result = NULL ;
    qSQL = "" ;

	cnn = PQsetdbLogin( "127.0.0.1" ,
                        "5432" , NULL , NULL ,
                        "compset" , 
                        "postgres" ,
                        "root");
                        
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
	std::ifstream archivo;
	std::string texto[10];
	std::string Database, Host, Port, User, Password, Provider ;

	archivo.open("leer.txt",ios::in);

	if (archivo.fail()){
		std::cout<<"no se pudo leer";
	}
	int i=0;
	while( !archivo.eof() ) {
        getline(archivo,texto[i]);

        std::cout << texto[i] << endl ;
        i++ ;
        Database = texto[0] ;
        Host = texto[1] ;
        Port = texto[2] ;
        User = texto[3] ;
        Password = texto[4] ;
        
    }
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
