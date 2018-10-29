#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../../include/ DBGeneratorPostgre.cpp -o DBGeneratorPostgre.so
