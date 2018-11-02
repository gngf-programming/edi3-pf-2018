g++ -shared -Wall -std=c++11 DBGeneratorMariaDB.cpp -o DBGeneratorMariaDB.dll -I./include -I../../../include/compset vendors\libmysql.dll
g++ -Wall -std=c++11 test.cpp include\DBGeneratorMariaDB.h -o test.exe -I./include -I../../../include/compset vendors\libmysql.dll lib\DBGeneratorMariaDB.dll
