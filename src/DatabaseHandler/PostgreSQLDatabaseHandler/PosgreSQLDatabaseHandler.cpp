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

class PosgreSQLDatabaseHandler : public DatabaseHandlerInterface, public ComponentInterface {

    public:
        PosgreSQLDatabaseHandler() ;
        virtual ~PosgreSQLDatabaseHandler() ;
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

PosgreSQLDatabaseHandler::PosgreSQLDatabaseHandler () {
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

PosgreSQLDatabaseHandler::~PosgreSQLDatabaseHandler() {
	if ( connected ) {
    	PQclear( result ) ;
    	PQfinish( cnn ) ;
	}
}

void PosgreSQLDatabaseHandler::prepareQuery( std::string query ) {
    qSQL = query ;
}

void PosgreSQLDatabaseHandler::ReadConfig() {
	std::string data[6];
    std::ifstream inifile;

	inifile.open( "config.ini", std::ios::in );

	if ( inifile.fail() ){
		std::cout << "no se pudo leer" ;
	}

	int i = 0 ;
	while( !inifile.eof() ) {

		std::getline( inifile , data[i] ) ;
		std::cout << data[i] << std::endl ;
                i++;
    }

    host = data[1].c_str() ;
    dataBase = data[2].c_str() ;
    port = data[3].c_str() ;
    user = data[4].c_str() ;
    passwd = data[5].c_str() ;
}

void PosgreSQLDatabaseHandler::execute() {
    
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

bool PosgreSQLDatabaseHandler::getErrorStatus() {
    return isError ;
}

void PosgreSQLDatabaseHandler::addParameter( int key, std::string value ) {
    std::cout<< "parametro " << value << std::endl ;
}

Row PosgreSQLDatabaseHandler::fetch() {
    Row row ;
    int columnCount = PQnfields(result);
    for ( int i = 0 ; i < columnCount ; i++ ) {
        std::string columnName = std::string( PQfname( result, i ) );
        std::string columnValue = std::string( PQgetvalue( result , 0 , i ) );
        row[columnName] = columnValue;    
    }
    return row; 
}

Table PosgreSQLDatabaseHandler::fetchAll() {
    Table result ;
    return result ;
}

//ComponentInterface:
bool PosgreSQLDatabaseHandler::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "DatabaseHandlerInterface") ?
        implemented = true
            : implemented = false;
}

void* PosgreSQLDatabaseHandler::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void PosgreSQLDatabaseHandler::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create();

ComponentInterface* create()
{
    return (ComponentInterface*) new PosgreSQLDatabaseHandler;
}
/* void readfile();

    int main()
{
    readfile();

    return 0;
}
void readfile(){

	ifstream archivo;
	string texto[10];
	string Database,Host,Port, User, Password, Provider;

	archivo.open("leer.txt",ios::in);

	if (archivo.fail()){
		cout<<"no se pudo leer";
	}
	int i=0;
	while(!archivo.eof()){

    getline(archivo,texto[i]);

    cout<<texto[i]<<endl;
    i++;
    Database=texto[0];
    Host=texto[1];
    Port=texto[2];
    User=texto[3];
    Password=texto[4];
    Provider=texto[5];
    }


}*/