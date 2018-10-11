#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ RequestHandler.cpp -o RequestHandler.so 
