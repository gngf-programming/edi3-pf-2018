#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../../include/ TestRequestResponse.cpp -o TestRequestResponse.so
