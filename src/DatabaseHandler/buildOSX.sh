#!/bin/bash
#g++ -shared -Wall -std=c++11 -fPIC -I../../include/ PostgreSQLDatabaseHandler.cpp -o JsonDocumentGenerator.dylib 

g++ -shared -Wall -std=c++11 -fPIC -I../../include/ -I/Library/PostgreSQL/11/include/ PostgreSQLDatabaseHandler.cpp -lpq -o PostgreSQLDatabaseHandler.dylib