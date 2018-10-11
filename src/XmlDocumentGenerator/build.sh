#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ XmlDocumentGenerator.cpp -o XmlDocumentGenerator.so 
