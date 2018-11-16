#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

#include <compset/ComponentInterface.h>
#include <compset/ComponentFactory.h>
#include <compset/DatabaseHandlerInterface.h>



int main()
{
    ComponentFactory* componentFactoryObject = new ComponentFactory();
    componentFactoryObject->setInterfaceName("DatabaseHandlerInterface");
    ComponentInterface* databaseHandlerComponent = componentFactoryObject->createFrom("../bin/mdb-app");
    DatabaseHandlerInterface* databaseHandlerObject = ( (DatabaseHandlerInterface*) databaseHandlerComponent->getInstance() );
    databaseHandlerObject->prepareQuery( "CREATE TABLE Programadores(Id INT, Name varchar(45), edad INT)" ) ; // WHERE %i = %j" ) ;
//    databaseHandlerObject->addParameter( ) ;
    databaseHandlerObject->execute() ;

    system("pause");
    delete componentFactoryObject;

    return 0;
}