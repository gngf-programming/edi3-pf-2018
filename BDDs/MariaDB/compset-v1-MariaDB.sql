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
-- ERASE AND CREATE TABLE USERS
-- ----------------------------------------------------------
DROP TABLE IF EXISTS compset.Users;

CREATE TABLE IF NOT EXISTS compset.Users
(
	idUsers INT UNSIGNED NOT NULL AUTO_INCREMENT,
	identifier VARCHAR(256) NULL,
	passwordHash VARCHAR(256) NULL,

	PRIMARY KEY (idUsers)
)
ENGINE = InnoDB;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- ERASE AND CREATE TABLE ROLES
-- ----------------------------------------------------------
DROP TABLE IF EXISTS compset.Roles;

CREATE TABLE IF NOT EXISTS compset.Roles
(
	idRoles INT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(256) NOT NULL,
	description VARCHAR(256) NULL,

	PRIMARY KEY (idRoles)
)
ENGINE = InnoDB;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- ERASE AND CREATE TABLE ACTIONS
-- ----------------------------------------------------------
DROP TABLE IF EXISTS compset.Actions;

CREATE TABLE IF NOT EXISTS compset.Actions
(
	idActions INT UNSIGNED NOT NULL AUTO_INCREMENT,
	name VARCHAR(256) NOT NULL,

	PRIMARY KEY (idActions)
)
ENGINE = InnoDB;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- ERASE AND CREATE TABLE UsersHasRoles
-- ----------------------------------------------------------
DROP TABLE IF EXISTS compset.UsersHasRoles;

CREATE TABLE IF NOT EXISTS compset.UsersHasRoles
(
	idUsersHasRoles INT UNSIGNED NOT NULL AUTO_INCREMENT,
	usersId INT UNSIGNED NOT NULL,
	rolesId INT UNSIGNED NOT NULL,

	PRIMARY KEY (idUsersHasRoles)
)
ENGINE = InnoDB;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- CREATION OF FOREIGN KEYS UsersHasRoles
-- ----------------------------------------------------------
ALTER TABLE compset.UsersHasRoles
	ADD CONSTRAINT fk_UHR_idUsers
        FOREIGN KEY (usersId)
        REFERENCES Users(idUsers)
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,

    ADD CONSTRAINT fk_UHR_idRoles
        FOREIGN KEY (rolesId)
        REFERENCES Roles(idRoles)
        ON UPDATE NO ACTION
        ON DELETE NO ACTION;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- ERASE AND CREATE TABLE RolesHasActions
-- ----------------------------------------------------------
DROP TABLE IF EXISTS compset.RolesHasActions;

CREATE TABLE IF NOT EXISTS compset.RolesHasActions
(
	idRolesHasActions INT UNSIGNED NOT NULL AUTO_INCREMENT,
	actionsId INT UNSIGNED NOT NULL,
	rolesId INT UNSIGNED NOT NULL,

	PRIMARY KEY (idRolesHasActions)
)
ENGINE = InnoDB;
-- ----------------------------------------------------------
-- ----------------------------------------------------------

-- ----------------------------------------------------------
-- CREATION OF FOREIGN KEYS RolesHasActions
-- ----------------------------------------------------------
ALTER TABLE compset.RolesHasActions
	ADD CONSTRAINT fk_RHA_idActions
        FOREIGN KEY (actionsId)
        REFERENCES Actions(idActions)
        ON UPDATE NO ACTION
        ON DELETE NO ACTION,

    ADD CONSTRAINT fk_RHA_idRoles
        FOREIGN KEY (rolesId)
        REFERENCES Roles(idRoles)
        ON UPDATE NO ACTION
        ON DELETE NO ACTION;
-- ----------------------------------------------------------
-- ----------------------------------------------------------