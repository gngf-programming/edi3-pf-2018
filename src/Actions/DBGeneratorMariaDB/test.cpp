/*
-- Copyright (c) 2018 Facundo Campos <facundo.nicolas.campos@gmail.com>. All rights reserved. 
-- File: DBGeneratorMariaDB\test.cpp. This file is part of COMPSET.
-- Released under the GPL3 license
-- https://opensource.org/licenses/GPL-3.0
*/
#include <DBGeneratorMariaDB.h>

using namespace std;

int main()
{
    DBGeneratorMariaDB db;
    db.execute();
    return 0;
}