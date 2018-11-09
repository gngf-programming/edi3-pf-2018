#!/bin/bash
g++ -shared -Wall -std=c++11 -lsqlite3 -fPIC -I../../../include/ SqliteDatabaseHandler.cpp -o SqliteDatabaseHandler.so 
