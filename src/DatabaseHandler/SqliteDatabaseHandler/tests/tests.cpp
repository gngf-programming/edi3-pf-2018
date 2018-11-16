#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <C:\Users\Diego\Documents\Sistemas\EDI 3\011 15-11-18 #\edi3-pf-2018\include\compset\ComponentInterface.h>
#include <C:\Users\Diego\Documents\Sistemas\EDI 3\011 15-11-18 #\edi3-pf-2018\include\compset\ComponentFactory.h>
#include <C:\Users\Diego\Documents\Sistemas\EDI 3\011 15-11-18 #\edi3-pf-2018\include\compset\DatabaseHandlerInterface.h>
#include "sqlite3.h"


typedef std::unordered_map< std::string, std::string > Row; 
typedef std::vector< Row > Table; 

int main()
{
	ComponentFactory* componentFactoryObject = new ComponentFactory();
    componentFactoryObject->setInterfaceName("DatabaseHandlerInterface");
    ComponentInterface* databaseHandlerComponent = componentFactoryObject->createFrom("../SqliteDatabaseHandler");
    DatabaseHandlerInterface* databaseHandlerObject = ( (DatabaseHandlerInterface*) databaseHandlerComponent->getInstance() );
	
	delete componentFactoryObject;
	
	databaseHandlerObject->prepareQuery( "CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)" );	
	databaseHandlerObject->execute();
	return 0;
	
	databaseHandlerObject->prepareQuery ( "INSERT INTO Users(name) VALUES(?)" );
	databaseHandlerObject->addParameter( 1, "Pedro" );
	databaseHandlerObject->addParameter( 2, "Albert" );
	databaseHandlerObject->execute ();
	
	system ("pause");
	
	Row firstRow = databaseHandlerObject->fetch() ;
	for (std::pair<std::string, std::string> element : firstRow )
    {
        std::cout << element.first << " :: " << element.second << std::endl ;
    }      
    /////////////////////////////////////////////////////////////////
    sqlite3_stmt * stmt = nullptr;
    
    sqlite3_step(stmt);
    
     Row row;
    int columnCount = sqlite3_column_count(stmt);
    for( int i = 0; i < columnCount; i++ )
    {
        std::string columnName = std::string( (char *)sqlite3_column_name(stmt, i) );
        std::string columnValue = std::string( (char *)sqlite3_column_text( stmt, i ) );
        row[columnName] = columnValue;           
    }    
    
     Table table;
    row.clear();
    columnCount = sqlite3_column_count(stmt);
    std::string columnName;
    std::string columnValue;
    while(sqlite3_step(stmt)==SQLITE_ROW)
    {
        row.clear();
        for( int i = 0; i < columnCount; i++ )
        {
            columnName = std::string( (char *)sqlite3_column_name(stmt, i) );
            columnValue = std::string( (char *)sqlite3_column_text( stmt, i ) );
            row[columnName] = columnValue;
        } 
        table.push_back(row);
    }
    
    std::cout << "Table DATA row 1:" << std::endl;
    std::cout << "id: " << table[0]["id"] << std::endl;
    std::cout << "name: " << table[0]["name"] << std::endl << std::endl;
   
   ///////////////////////////////////////////////////////////////////////
    
	system ("pause");

	return 0;
}
	/*
	
	    std::string query = "CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)";
    iReturn = sqlite3_exec(pDB, query.c_str(), NULL, NULL, NULL);
    if (iReturn != SQLITE_OK) { sqlite3_close(pDB); return 1; }

    // insert data using binding
    sqlite3_stmt * stmt = nullptr;
    query = "INSERT INTO Users(name) VALUES(?)";
    iReturn = sqlite3_prepare_v2(pDB, query.c_str(), query.size() + 1, &stmt, nullptr);
    if (iReturn != SQLITE_OK) { sqlite3_close(pDB); return 1; }

    // binding 1
    std::string name1 = "Juan"; 
    iReturn = sqlite3_bind_text(stmt, 1, name1.c_str(), name1.size(), 0);
    if (iReturn != SQLITE_OK) { return 1; }
    // commit 
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);

    // binding 2
    std::string name2 = "Pedro"; 
    iReturn = sqlite3_bind_text(stmt, 1, name2.c_str(), name2.size(), 0);
    if (iReturn != SQLITE_OK) { return 1; }
    // commit 
    sqlite3_step(stmt);
    sqlite3_reset(stmt);
    sqlite3_clear_bindings(stmt);
	
}
*/
