g++ -c -shared -o DBGeneratorMariaDB.o DBGeneratorMariaDB.cpp -Wall -std=c++11 -I. -I-./include -I../../../include/compset
g++ -c -o test.o test.cpp -Wall -std=c++11 -I. -I./include -I../../../include/compset
g++ -o test_db_generator *.o -Wall -std=c++11 -I. -I./include -I../../../include/compset -I./include/mysql -L./lib -llibmariadb -lmariadbclient