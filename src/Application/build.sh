#!/bin/bash
g++ -shared -Wall -std=c++11 -fPIC -I../../include/ Application.cpp -o Application.so
