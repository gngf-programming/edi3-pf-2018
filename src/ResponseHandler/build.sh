#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ ResponseHandler.cpp -o ResponseHandler.so 
