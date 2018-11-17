::-- Copyright (c) 2018 Facundo Campos <facundo.nicolas.campos@gmail.com>. All rights reserved. 
::-- File: DBGeneratorMariaDB\build.bat. This file is part of COMPSET.
::-- Released under the GPL3 license
::-- https://opensource.org/licenses/GPL-3.0

g++ -shared -Wall -std=c++11 DBGeneratorMariaDB.cpp -o lib\DBGeneratorMariaDB.dll -I./include -I../../../include/compset vendors\libmysql.dll
g++ -Wall -std=c++11 test.cpp include\DBGeneratorMariaDB.h -o test.exe -I./include -I../../../include/compset vendors\libmysql.dll lib\DBGeneratorMariaDB.dll
