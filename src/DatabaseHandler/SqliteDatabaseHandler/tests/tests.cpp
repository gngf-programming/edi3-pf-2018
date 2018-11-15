#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <compset/ComponentInterface.h>
#include <compset/ComponentFactory.h>
#include <compset/DatabaseHandlerInterface.h>

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
}
