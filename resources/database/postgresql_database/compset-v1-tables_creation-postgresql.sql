-- Author: Facundo Campos
-- MGBD: PostgreSQL
-- DB Name: compset

-- ----------------------------------------
-- Creating Collation for Unicode Standard
-- ----------------------------------------
--DROP COLLATION IF EXISTS compset.utf8_unicode;
--CREATE COLLATION compset.utf8_unicode
    --FROM pg_catalog."und-x-icu";

--ALTER COLLATION utf8_unicode OWNER TO postgres;

DROP COLLATION IF EXISTS public.utf8_unicode CASCADE;
CREATE COLLATION public.utf8_unicode
    FROM pg_catalog."und-x-icu";

ALTER COLLATION public.utf8_unicode OWNER TO postgres;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Creating table "users"
-- ----------------------------------------

-- Creating autoincremental type
drop sequence IF EXISTS users_id_seq CASCADE;
create sequence users_id_seq;

drop table IF EXISTS users CASCADE;
create table users
(
	id_users BIGINT NOT NULL UNIQUE DEFAULT nextval('users_id_seq'),
	identifier VARCHAR(256) COLLATE utf8_unicode,
	password_hash VARCHAR(256) COLLATE utf8_unicode
);

-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Creating table "roles"
-- ----------------------------------------

-- Creating autoincremental type
drop sequence IF EXISTS roles_id_seq CASCADE;
create sequence roles_id_seq;

drop table IF EXISTS roles CASCADE;
create table roles
(
	id_roles BIGINT NOT NULL UNIQUE DEFAULT nextval('roles_id_seq'),
	name VARCHAR(256) COLLATE utf8_unicode,
	description VARCHAR(256) COLLATE utf8_unicode
);

-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Creating table "actions"
-- ----------------------------------------

-- Creating autoincremental type
drop sequence IF EXISTS actions_id_seq CASCADE;
create sequence actions_id_seq;

drop table IF EXISTS actions CASCADE;
create table actions
(
	id_actions BIGINT NOT NULL UNIQUE DEFAULT nextval('actions_id_seq'),
	name VARCHAR(256) COLLATE utf8_unicode
);

-- ----------------------------------------
-- ----------------------------------------


-- ----------------------------------------
-- Creating table "users_has_roles"
-- ----------------------------------------

-- Creating autoincremental type
drop sequence IF EXISTS users_has_roles_id_seq CASCADE;
create sequence users_has_roles_id_seq;

drop table IF EXISTS users_has_roles CASCADE;
create table users_has_roles
(
	id_users_has_roles BIGINT NOT NULL UNIQUE DEFAULT nextval('users_has_roles_id_seq'),
	users_id BIGINT NOT NULL,
	roles_id BIGINT NOT NULL	
);

-- Agregar claves foraneas
alter table users_has_roles
	add constraint fk_uhr_users_id
	foreign key (users_id)
	references users(id_users)
	on delete CASCADE
	on update NO ACTION,
	
	add constraint fk_uhr_roles_id
	foreign key (roles_id)
	references roles(id_roles)
	on delete CASCADE
	on update NO ACTION;

-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Creating table "roles_has_actions"
-- ----------------------------------------

-- Creating autoincremental type
drop sequence IF EXISTS roles_has_actions_id_seq CASCADE;
create sequence roles_has_actions_id_seq;

drop table IF EXISTS roles_has_actions CASCADE;
create table roles_has_actions
(
	id_roles_has_actions BIGINT NOT NULL UNIQUE DEFAULT nextval('roles_has_actions_id_seq'),
	actions_id BIGINT NOT NULL,
	roles_id BIGINT NOT NULL	
);

-- Agregar claves foraneas
alter table roles_has_actions
	add constraint fk_rha_actions_id
	foreign key (actions_id)
	references actions(id_actions)
	on delete CASCADE
	on update NO ACTION,
	
	add constraint fk_rha_roles_id
	foreign key (roles_id)
	references roles(id_roles)
	on delete CASCADE
	on update NO ACTION;

-- ----------------------------------------
-- ----------------------------------------