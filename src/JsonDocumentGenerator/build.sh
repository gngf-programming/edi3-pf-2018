#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ JsonDocumentGenerator.cpp -o JsonDocumentGenerator.so 
