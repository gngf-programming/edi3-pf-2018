#include "DBGeneratorMariaDB.h"

// a sample exported function
DBGeneratorMariaDB::DBGeneratorMariaDB() : referenceCounter(0){
    MY_HOSTNAME = "localhost";
    MY_DATABASE = "compset";
    MY_USERNAME = "root";
    MY_PASSWORD = "root";
    MY_SOCKET   = NULL;
}

DBGeneratorMariaDB::~DBGeneratorMariaDB(){}

int DBGeneratorMariaDB::execute()
{
    MYSQL *mariadb = NULL;

    try {
            mariadb = mysql_init(mariadb);

            // Intentar iniciar MySQL:
            if (!mariadb)
            {
                std::cout << "Init faild, out of memory?" << std::endl;
                return EXIT_FAILURE;
            }

            if( !mysql_real_connect(
                                    mariadb,
                                    MY_HOSTNAME,
                                    MY_USERNAME,
                                    MY_PASSWORD,
                                    MY_DATABASE,
                                    MY_PORT_NO,
                                    MY_SOCKET,
                                    MY_OPT
                                    )
            )
            {
                // No se puede conectar con el servidor en el puerto especificado.
                std::cout << "Imposible to connect to the database." << std::endl;
                std::cout << "Error: " << mysql_error(mariadb) << std::endl;
                std::cout << "Error Nro: " << mysql_errno(mariadb) << std::endl;
                mysql_close(mariadb);
                return EXIT_FAILURE;
            } else
            {
                std::cout << "Successful established connection" << std::endl;
            }

            std::fstream query("querys.sql", std::ios::in);

            std::string line;
            const char* commands;

            if ( query.is_open() )
            {
                //realizar consultas
                do
                {
                    getline(query, line );
                    commands = line.c_str();
                    if( mysql_query ( mariadb, commands ) )
                    {
                        // Error al realizar la consulta:
                        std::cout << "Error: " << mysql_error(mariadb) << std::endl;
                        std::cout << "Error Nro: " << mysql_errno(mariadb) << std::endl;
                        mysql_close(mariadb);
                        rewind(stdin);
                    }
                }while( !query.eof() );
                query.close();
                return EXIT_SUCCESS;
            }
            else
            {
                query.close();
                std::cout << "Imposible read sql file. Check its existence in the right directory "<<std::endl;
                return EXIT_FAILURE;
            }

            // Hacer una consulta":
            std::cout << "Error: " << mysql_error(mariadb) << std::endl;
            std::cout << "Error Nro: " << mysql_errno(mariadb) << std::endl;

            mysql_close(mariadb);
        }
        catch (char *e)
        {
            std::cerr << "[EXCEPTION] " << e << std::endl;
            return false;
        }

    getchar();
    return EXIT_FAILURE;
}

/********************************************************************************************/
/*COMPONENT SECTION INTERFACE*/
bool DBGeneratorMariaDB::implements(std::string interfaceName)
{
    return (interfaceName == "ComponentInterface" || interfaceName == "ActionInterface") ?
        implemented = true
            : implemented = false;
}

void* DBGeneratorMariaDB::getInstance()
{
    if(implemented) {  referenceCounter++;  return this; }
    return NULL;
}

void DBGeneratorMariaDB::release()
{
    referenceCounter--;
    if(referenceCounter <= 0) delete this;
}

extern "C" ComponentInterface* create()
{
    return (ComponentInterface*) new DBGeneratorMariaDB;
}
