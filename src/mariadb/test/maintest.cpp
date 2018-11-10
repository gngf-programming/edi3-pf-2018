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
    databaseHandlerObject->prepareQuery( "SELECT * FROM users" ) ; // WHERE %i = %j" ) ;
    databaseHandlerObject->addParameter( 0, "gabi") ;
    databaseHandlerObject->execute() ;
   // Row firstRow = databaseHandlerObject->fetch() ;

  

 /*   for (std::pair<std::string, std::string> element : firstRow )
    {
        std::cout << element.first << " :: " << element.second << std::endl ;
    }

 */
    system("pause");
    delete componentFactoryObject;

    return 0;
}