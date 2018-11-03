-- ----------------------------------------
-- ----------------------------------------
-- Stored Procedures for MariaDB database
-- ----------------------------------------
-- Copyright (c) 2018 Facundo Campos <facundo.nicolas.campos@gmail.com>. All rights reserved. 
-- This file is part of COMPSET.
-- Released under the GPL3 license
-- https://opensource.org/licenses/GPL-3.0

-- ----------------------------------------
-- ----------------------------------------


-- ----------------------------------------
-- Alta de user
-- ----------------------------------------
DELIMITER $$
drop procedure if exists `compset`.`c_user`;
CREATE PROCEDURE `compset`.`c_user` 
( 
	IN _identifier VARCHAR(256),
	IN _password_hash VARCHAR(256)
	
)
BEGIN
  insert into users(identifier, password_hash)
  	values (_identifier,_password_hash);
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Alta de roles
-- ----------------------------------------
DELIMITER $$
drop procedure if exists `compset`.`c_rol`;
CREATE PROCEDURE `compset`.`c_rol` 
( 
	IN _name VARCHAR(256),
	IN _description VARCHAR(256) 
)
BEGIN
  insert into roles(name, description)
  	values (_name,_description);
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Alta de action
-- ----------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`c_action`;
CREATE PROCEDURE `compset`.`c_action` 
( 
	IN _name VARCHAR(256)
)
BEGIN
  insert into actions(name)
  	values (_name);
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Alta de users_has_roles
-- ----------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`c_b_uhr`;
CREATE PROCEDURE `compset`.`c_b_uhr` 
( 
	IN _users_id BIGINT,
	IN _roles_id BIGINT
)
BEGIN
  insert into users_has_roles(users_id, roles_id)
  	values (_users_id, _roles_id);
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Alta de roles_has_actions
-- ----------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`c_b_rha`;
CREATE PROCEDURE `compset`.`c_b_rha` 
( 
	IN _roles_id BIGINT,
	IN _actions_id BIGINT
	
)
BEGIN
  insert into roles_has_actions(roles_id, actions_id)
  	values (_roles_id, _actions_id );
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------


-- ---------------------------------------------


-- ----------------------------------------
-- baja de user
-- ----------------------------------------
DELIMITER $$
drop procedure if exists `compset`.`d_user_by_id`;
CREATE PROCEDURE `compset`.`d_user_by_id` 
( 
	IN _id_users BIGINT
)
BEGIN
	delete from users 
		where id_users = _id_users
		order by id_users;
	call d_b_uhr_by_user_id( _id_users );
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- baja de roles
-- ----------------------------------------
DELIMITER $$
drop procedure if exists `compset`.`d_rol_by_id`;
CREATE PROCEDURE `compset`.`d_rol_by_id` 
( 
	IN _id_roles BIGINT
)
BEGIN
	delete from roles 
		where id_roles = _id_roles
		order by id_roles;
	call d_b_uhr_by_roles_id( _id_roles );
	call d_b_rha_by_roles_id( _id_roles );
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- baja de action
-- ----------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`d_action_by_id`;
CREATE PROCEDURE `compset`.`d_action_by_id` 
( 
	IN _id_actions BIGINT
)
BEGIN
	delete from actions 
			where id_actions = _id_actions
			order by id_actions;
	call d_b_rha_by_actions_id(_id_actions);
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- baja de users_has_roles
-- ----------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`d_b_uhr_by_id`;
CREATE PROCEDURE `compset`.`d_b_uhr_by_id` 
( 
	IN _id_users_has_roles BIGINT
)
BEGIN
  delete from users_has_roles 
		where id_users_has_roles = _id_users_has_roles
		order by id_users_has_roles;
END $$
DELIMITER ;
-- --------------------------------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`d_b_uhr_by_user_id`;
CREATE PROCEDURE `compset`.`d_b_uhr_by_user_id` 
( 
	IN _users_id BIGINT
)
BEGIN
  delete from users_has_roles 
		where users_id = _users_id
		order by id_users_has_roles;
END $$
DELIMITER ;
-- --------------------------------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`d_b_uhr_by_roles_id`;
CREATE PROCEDURE `compset`.`d_b_uhr_by_roles_id` 
( 
	IN _roles_id BIGINT
)
BEGIN
  delete from users_has_roles 
		where roles_id = _roles_id
		order by id_users_has_roles;
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- baja de roles_has_actions
-- ----------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`d_b_rha_by_id`;
CREATE PROCEDURE `compset`.`d_b_rha_by_id` 
( 
	IN _id_roles_has_actions BIGINT
)
BEGIN
	delete from roles_has_actions 
		where id_roles_has_actions = _id_roles_has_actions
		order by id_roles_has_actions;
END $$
DELIMITER ;

-- -------------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`d_b_rha_by_roles_id`;
CREATE PROCEDURE `compset`.`d_b_rha_by_roles_id` 
( 
	IN _roles_id BIGINT
)
BEGIN
	delete from roles_has_actions 
		where roles_id = _roles_id
		order by id_roles_has_actions;
END $$
DELIMITER ;

-- --------------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`d_b_rha_by_actions_id`;
CREATE PROCEDURE `compset`.`d_b_rha_by_actions_id` 
( 
	IN _actions_id BIGINT
)
BEGIN
  delete from roles_has_actions 
		where actions_id = _actions_id
		order by id_roles_has_actions;
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- -----------------------------------------------------------------

-- ----------------------------------------
-- Modificacion de user
-- ----------------------------------------
DELIMITER $$
drop procedure if exists `compset`.`u_user_by_id`;
CREATE PROCEDURE `compset`.`u_user_by_id` 
( 
	IN _id_users BIGINT,
	IN _identifier VARCHAR(256),
	IN _password_hash VARCHAR(256) 
)
BEGIN
  update users 
  	set identifier = _identifier,
  		password_hash = _password_hash
  	where id_users = _id_users;
END $$
DELIMITER ;

-- ----------------------------------------------

DELIMITER $$
drop procedure if exists `compset`.`u_user_identifier_by_id`;
CREATE PROCEDURE `compset`.`u_user_identifier_by_id` 
( 
	IN _id_users BIGINT,
	IN _identifier VARCHAR(256)
)
BEGIN
  update users 
  	set identifier = _identifier
  	where id_users = _id_users;
END $$
DELIMITER ;

-- ----------------------------------------------

DELIMITER $$
drop procedure if exists `compset`.`u_user_pwd_hash_by_id`;
CREATE PROCEDURE `compset`.`u_user_pwd_hash_by_id` 
( 
	IN _id_users BIGINT,
	IN _password_hash VARCHAR(256)
)
BEGIN
  update users 
  	set password_hash = _password_hash
  	where id_users = _id_users;
END $$
DELIMITER ;

-- -------------------------------------------------------

DELIMITER $$
drop procedure if exists `compset`.`u_user_by_identifier`;
CREATE PROCEDURE `compset`.`u_user_by_identifier` 
( 
	IN _identifier VARCHAR(256),
	IN _new_identifier VARCHAR(256),
	IN _password_hash VARCHAR(256) 
)
BEGIN
  update users 
  	set identifier = _new_identifier,
  		password_hash = _password_hash
  	where identifier = _identifier;
END $$
DELIMITER ;

-- -------------------------------------------------------

DELIMITER $$
drop procedure if exists `compset`.`u_user_identifier_by_identifier`;
CREATE PROCEDURE `compset`.`u_user_identifier_by_identifier` 
( 
	IN _identifier VARCHAR(256),
	IN _new_identifier VARCHAR(256)
)
BEGIN
  update users 
  	set identifier = _new_identifier
  	where identifier = _identifier;
END $$
DELIMITER ;

-- -------------------------------------------------------

DELIMITER $$
drop procedure if exists `compset`.`u_user_pwd_hash_by_identifier`;
CREATE PROCEDURE `compset`.`u_user_pwd_hash_by_identifier` 
( 
	IN _identifier VARCHAR(256),
	IN _password_hash VARCHAR(256) 
)
BEGIN
  update users 
  	set password_hash = _password_hash
  	where identifier = _identifier;
END $$
DELIMITER ;

-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Modificacion de roles
-- ----------------------------------------
DELIMITER $$
drop procedure if exists `compset`.`u_rol_by_id`;
CREATE PROCEDURE `compset`.`u_rol_by_id` 
( 
	IN _id_roles BIGINT,
	IN _name VARCHAR(256),
	IN _description VARCHAR(256) 
)
BEGIN
  update roles
  	set name = _name,
   		description = _description
  	where id_roles = _id_roles;
END $$
DELIMITER ;

-- ----------------------------------------------

DELIMITER $$
drop procedure if exists `compset`.`u_rol_name_by_id`;
CREATE PROCEDURE `compset`.`u_rol_name_by_id` 
( 
	IN _id_roles BIGINT,
	IN _name VARCHAR(256)
)
BEGIN
  update roles
  	set name = _name
  	where id_roles = _id_roles;
END $$
DELIMITER ;

-- -----------------------------------------------

DELIMITER $$
drop procedure if exists `compset`.`u_rol_description_by_id`;
CREATE PROCEDURE `compset`.`u_rol_description_by_id` 
( 
	IN _id_roles BIGINT
	IN _description VARCHAR(256) 
)
BEGIN
  update roles
  	set description = _description
  	where id_roles = _id_roles;
END $$
DELIMITER ;

-- ---------------------------------------------------

DELIMITER $$
drop procedure if exists `compset`.`u_rol_by_name`;
CREATE PROCEDURE `compset`.`u_rol_by_name` 
( 
	IN _name VARCHAR(256),
	IN _new_name VARCHAR(256),
	IN _description VARCHAR(256) 
)
BEGIN
  update roles
  	set name = _new_name,
   		description = _description
  	where name = _name;
END $$
DELIMITER ;

-- ---------------------------------------------------

DELIMITER $$
drop procedure if exists `compset`.`u_rol_name_by_name`;
CREATE PROCEDURE `compset`.`u_rol_name_by_name` 
( 
	IN _name VARCHAR(256),
	IN _new_name VARCHAR(256)
)
BEGIN
  update roles
  	set name = _new_name
  	where name = _name;
END $$
DELIMITER ;

-- ---------------------------------------------------

DELIMITER $$
drop procedure if exists `compset`.`u_rol_description_by_name`;
CREATE PROCEDURE `compset`.`u_rol_description_by_name` 
( 
	IN _name VARCHAR(256),
	IN _description VARCHAR(256) 
)
BEGIN
  update roles
  	set description = _description
  	where name = _name;
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Modificacion de action
-- ----------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_action_by_id`;
CREATE PROCEDURE `compset`.`u_action_by_id` 
( 
	IN _id_actions BIGINT,
	IN _name VARCHAR(256)
)
BEGIN
  update actions 
  	set name = _name
  	where id_actions = _id_actions;
END $$
DELIMITER ;

-- ----------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_action_by_name`;
CREATE PROCEDURE `compset`.`u_action_by_name` 
( 
	IN _name VARCHAR(256),
	IN _new_name VARCHAR(256)
)
BEGIN
  update actions 
  	set name = _new_name
  	where name = _name;
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- modificar users_has_roles
-- ----------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_b_uhr_by_id`;
CREATE PROCEDURE `compset`.`u_b_uhr_by_id` 
( 
	IN _id_users_has_roles BIGINT,
	IN _users_id BIGINT,
	IN _roles_id BIGINT
)
BEGIN
  update users_has_roles
  	set users_id = _users_id,
  		roles_id = _roles_id
  	where id_actions = _id_actions;
END $$
DELIMITER ;

-- --------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_b_uhr_user_id_by_id`;
CREATE PROCEDURE `compset`.`u_b_uhr_user_id_by_id` 
( 
	IN _id_users_has_roles BIGINT,
	IN _users_id BIGINT
)
BEGIN
  update users_has_roles
  	set users_id = _users_id
  	where id_actions = _id_actions;
END $$
DELIMITER ;

-- --------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_b_uhr_rol_id_by_id`;
CREATE PROCEDURE `compset`.`u_b_uhr_rol_id_by_id` 
( 
	IN _id_users_has_roles BIGINT,
	IN _roles_id BIGINT
)
BEGIN
  update users_has_roles
  	set roles_id = _roles_id
  	where id_actions = _id_actions;
END $$
DELIMITER ;

-- ------------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_b_uhr_user_id_by_user_id`;
CREATE PROCEDURE `compset`.`u_b_uhr_user_id_by_user_id` 
( 
	IN _users_id BIGINT,
	IN _new_user_id BIGINT
)
BEGIN
  update users_has_roles
  	set users_id = _new_user_id
  	where users_id = _users_id;
END $$
DELIMITER ;

-- ------------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_b_uhr_rol_id_by_rol_id`;
CREATE PROCEDURE `compset`.`u_b_uhr_rol_id_by_rol_id` 
( 
	IN _roles_id BIGINT
	IN _new_roles_id BIGINT
)
BEGIN
  update users_has_roles
  	set roles_id = _new_roles_id
  	where roles_id = _roles_id;
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- modificar roles_has_actions
-- ----------------------------------------
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_b_rha_by_id`;
CREATE PROCEDURE `compset`.`u_b_rha_by_id` 
( 
	IN _id_roles_has_actions BIGINT,
	IN _roles_id BIGINT,
	IN _actions_id BIGINT	
)
BEGIN
  update roles_has_actions
  	set roles_id = _roles_id,
  		actions = _actions_id
  	where id_roles_has_actions = _id_roles_has_actions;
END $$
DELIMITER ;

-- ----------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_b_rha_rol_id_by_id`;
CREATE PROCEDURE `compset`.`u_b_rha_rol_id_by_id` 
( 
	IN _id_roles_has_actions BIGINT,
	IN _roles_id BIGINT
)
BEGIN
  update roles_has_actions
  	set roles_id = _roles_id
  	where id_roles_has_actions = _id_roles_has_actions;
END $$
DELIMITER ;

-- ----------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_b_rha_action_id_by_id`;
CREATE PROCEDURE `compset`.`u_b_rha_action_id_by_id` 
( 
	IN _id_roles_has_actions BIGINT,
	IN _actions_id BIGINT
)
BEGIN
  update roles_has_actions
  	set actions_id = _actions_id
  	where id_roles_has_actions = _id_roles_has_actions;
END $$
DELIMITER ;

-- ----------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_b_rha_rol_id_by_rol_id`;
CREATE PROCEDURE `compset`.`u_b_rha_rol_id_by_rol_id` 
( 
	IN _roles_id BIGINT,
	IN _new_roles_id BIGINT
)
BEGIN
  update roles_has_actions
  	set roles_id = _new_roles_id
  	where roles_id = _roles_id;
END $$
DELIMITER ;

-- -----------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`u_b_rha_action_id_by_action_id`;
CREATE PROCEDURE `compset`.`u_b_rha_action_id_by_action_id` 
( 
	IN _actions_id BIGINT
	IN _new_actions_id BIGINT	
)
BEGIN
  update roles_has_actions
  	set actions = _new_actions_id
  	where actions_id = _actions_id;
END $$
DELIMITER ;
-- ----------------------------------------
-- ----------------------------------------


-- ---------------------------------------------

-- Obtener PK de users_has_roles con las FK de users y roles
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`get_uhr_id_by_fks`;
CREATE PROCEDURE `compset`.`get_uhr_id_by_fks`
(
	IN _users_id BIGINT,
	IN _roles_id BIGINT
)
BEGIN
	select id_users_has_roles 
	from users_has_roles
	where users_id = _users_id
	and roles_id = _roles_id
	limit 1; 
END $$
DELIMITER ;

-- Obtener PK de roles_has_actions con las FK de roles y actions
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`get_rha_id_by_fks`;
CREATE PROCEDURE `compset`.`get_rha_id_by_fks`
(
	IN _roles_id BIGINT,
	IN _actions_id BIGINT
)
BEGIN
	select id_roles_has_actions 
	from roles_has_actions
	where actions_id = _actions_id
	and roles_id = _roles_id
	limit 1; 
END $$
DELIMITER ;

-- Obtener PK de users a partir de identifier
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`get_id_users`;
CREATE PROCEDURE `compset`.`get_id_users`
(
	IN _identifier BIGINT
)
BEGIN
	select id_users 
	from users 
	where identifier = _identifier
	limit 1;
END $$
DELIMITER ;

-- Obtener PK de roles a partir de name
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`get_id_roles`;
CREATE PROCEDURE `compset`.`get_id_roles`
(
	IN _name BIGINT
)
BEGIN
	select id_roles 
	from roles 
	where name = _name
	limit 1;
END $$
DELIMITER ;

-- Obtener PK de actions a partir de name
DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`get_id_actions`;
CREATE PROCEDURE `compset`.`get_id_actions`
(
	IN _name BIGINT
)
BEGIN
	select id_actions 
	from actions 
	where name = _name
	limit 1;
END $$
DELIMITER ;

-- ---------------------------------------------------------------------
-- obtener los datos que estan relacionados entre users, roles y actions
-- ---------------------------------------------------------------------

DELIMITER $$
DROP PROCEDURE IF EXISTS `compset`.`get_all_common`;
CREATE PROCEDURE `compset`.`get_all_common`()
BEGIN
	select users.*,roles.*,actions.*
	from users 
	inner join users_has_roles 
		on users.id_users = users_has_roles.users_id
	inner join roles 
		on users_has_roles.roles_id = roles.id_roles
	inner join roles_has_actions 
		on roles.id_roles = roles_has_actions.roles_id
	inner join actions 
		on roles_has_actions.actions_id = actions.id_actions
	order by users.id_users;
END $$
DELIMITER ;

