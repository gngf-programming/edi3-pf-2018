-- Author: Facundo Campos
-- MGBDD: MariaDB
-- BDD Name: compset

-- ----------------------------------------------------------
-- ERASE IF EXISTS AND CREATE DATABASE
-- ----------------------------------------------------------
DROP DATABASE IF EXISTS compset;

CREATE DATABASE compset
	CHARACTER SET = 'utf8'
	COLLATE = 'utf8_unicode_ci';
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- ERASE AND CREATE TABLE users
-- ----------------------------------------------------------
DROP TABLE IF EXISTS compset.users CASCADE;

CREATE TABLE IF NOT EXISTS compset.users
(
	id_users BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
	identifier VARCHAR(256) NULL,
	password_hash VARCHAR(256) NULL,

	PRIMARY KEY (id_users)
)
ENGINE = InnoDB;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- ERASE AND CREATE TABLE roles
-- ----------------------------------------------------------
DROP TABLE IF EXISTS compset.roles CASCADE;

CREATE TABLE IF NOT EXISTS compset.roles
(
	id_roles BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(256) NOT NULL,
	description VARCHAR(256) NULL,

	PRIMARY KEY (id_roles)
)
ENGINE = InnoDB;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- ERASE AND CREATE TABLE actions
-- ----------------------------------------------------------
DROP TABLE IF EXISTS compset.actions CASCADE;

CREATE TABLE IF NOT EXISTS compset.actions
(
	id_actions BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(256) NOT NULL,

	PRIMARY KEY (id_actions)
)
ENGINE = InnoDB;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- ERASE AND CREATE TABLE users_has_roles
-- ----------------------------------------------------------
DROP TABLE IF EXISTS compset.users_has_roles CASCADE;

CREATE TABLE IF NOT EXISTS compset.users_has_roles
(
	id_users_has_roles BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
	users_id BIGINT UNSIGNED NOT NULL,
	roles_id BIGINT UNSIGNED NOT NULL,

	PRIMARY KEY (id_users_has_roles)
)
ENGINE = InnoDB;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- CREATION OF FOREIGN KEYS users_has_roles
-- ----------------------------------------------------------
ALTER TABLE compset.users_has_roles
	ADD CONSTRAINT fk_uhr_id_users
        FOREIGN KEY (users_id)
        REFERENCES users(id_users)
        ON UPDATE NO ACTION
        ON DELETE CASCADE,

    ADD CONSTRAINT fk_uhr_id_roles
        FOREIGN KEY (roles_id)
        REFERENCES roles(id_roles)
        ON UPDATE NO ACTION
        ON DELETE CASCADE;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- ERASE AND CREATE TABLE roles_has_actions
-- ----------------------------------------------------------
DROP TABLE IF EXISTS compset.roles_has_actions CASCADE;

CREATE TABLE IF NOT EXISTS compset.roles_has_actions
(
	id_roles_has_actions BIGINT UNSIGNED NOT NULL AUTO_INCREMENT,
	actions_id BIGINT UNSIGNED NOT NULL,
	roles_id BIGINT UNSIGNED NOT NULL,

	PRIMARY KEY (id_roles_has_actions)
)
ENGINE = InnoDB;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- CREATION OF FOREIGN KEYS roles_has_actions
-- ----------------------------------------------------------
ALTER TABLE compset.roles_has_actions
	ADD CONSTRAINT fk_rha_id_actions
        FOREIGN KEY (actions_id)
        REFERENCES actions(id_actions)
        ON UPDATE NO ACTION
        ON DELETE CASCADE,

    ADD CONSTRAINT fk_rha_id_roles
        FOREIGN KEY (roles_id)
        REFERENCES roles(id_roles)
        ON UPDATE NO ACTION
        ON DELETE CASCADE;
-- ----------------------------------------------------------
-- ----------------------------------------------------------