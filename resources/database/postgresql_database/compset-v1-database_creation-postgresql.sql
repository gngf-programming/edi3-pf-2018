-- Author: Facundo Campos
-- MGBD: PostgreSQL
-- DB Name: compset

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
