#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../../include/ DBGeneratorMariaDB.cpp -o DBGeneratorMariaDB.so
