-- Copyright (c) 2018 Facundo Campos <facundo.nicolas.campos@gmail.com>. All rights reserved.  
-- This file is part of COMPSET. 
-- Released under the GPL3 license 
-- https://opensource.org/licenses/GPL-3.0 

-- ----------------------------------------
-- Creating database "compset"
-- ----------------------------------------
DROP DATABASE IF EXISTS compset;
CREATE DATABASE compset
    WITH 
    OWNER = postgres
    TEMPLATE = template0
    ENCODING = 'UTF8'
    LC_COLLATE = 'C'
    LC_CTYPE = 'C'
    TABLESPACE = pg_default
    CONNECTION LIMIT = -1;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Conecting the database
-- ----------------------------------------
--\connect compset;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Creating Schema
-- ----------------------------------------
--DROP SCHEMA IF EXISTS compset CASCADE;
--CREATE SCHEMA compset
    --AUTHORIZATION postgres;
-- ----------------------------------------
-- ----------------------------------------
