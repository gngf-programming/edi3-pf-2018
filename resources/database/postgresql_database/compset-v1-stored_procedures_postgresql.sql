-- ----------------------------------------
-- ----------------------------------------
-- Stored Procedures for PostgreSQL database
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
DROP FUNCTION IF EXISTS c_user;
CREATE FUNCTION c_user  
( 
	IN _identifier VARCHAR(256),
	IN _password_hash VARCHAR(256)
	
) RETURNS void AS $$
BEGIN
	insert into users(identifier, password_hash)
  		   values (_identifier,_password_hash);
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Alta de roles
-- ----------------------------------------
DROP FUNCTION IF EXISTS c_rol;
CREATE FUNCTION c_rol  
( 
	IN _name VARCHAR(256),
	IN _description VARCHAR(256) 
) RETURNS void AS $$
BEGIN
	insert into roles(name, description)
		   values (_name,_description);
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Alta de action
-- ----------------------------------------
DROP FUNCTION IF EXISTS c_action;
CREATE FUNCTION c_action  
( 
	IN _name VARCHAR(256)
) RETURNS void AS $$
BEGIN
  insert into actions(name)
  	values (_name);
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Alta de users_has_roles
-- ----------------------------------------
DROP FUNCTION IF EXISTS c_b_uhr;
CREATE FUNCTION c_b_uhr  
( 
	IN _users_id BIGINT,
	IN _roles_id BIGINT
) RETURNS void AS $$
BEGIN
  insert into users_has_roles(users_id, roles_id)
  	values (_users_id, _roles_id);
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Alta de roles_has_actions
-- ----------------------------------------
DROP FUNCTION IF EXISTS c_b_rha;
CREATE FUNCTION c_b_rha  
( 
	IN _roles_id BIGINT,
	IN _actions_id BIGINT
	
) RETURNS void AS $$
BEGIN
  insert into roles_has_actions(roles_id, actions_id)
  	values (_roles_id, _actions_id );
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------


-- ---------------------------------------------


-- ----------------------------------------
-- baja de user
-- ----------------------------------------
DROP FUNCTION IF EXISTS d_user_by_id;
CREATE FUNCTION d_user_by_id  
( 
	IN _id_users BIGINT
) RETURNS void AS $$
BEGIN
	delete from users 
		where id_users = _id_users;
	perform d_b_uhr_by_user_id( _id_users );
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- baja de roles
-- ----------------------------------------
DROP FUNCTION IF EXISTS d_rol_by_id;
CREATE FUNCTION d_rol_by_id  
( 
	IN _id_roles BIGINT
) RETURNS void AS $$
BEGIN
	delete from roles 
		where id_roles = _id_roles;
	perform d_b_uhr_by_roles_id( _id_roles );
	perform d_b_rha_by_roles_id( _id_roles );
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- baja de action
-- ----------------------------------------
DROP FUNCTION IF EXISTS d_action_by_id;
CREATE FUNCTION d_action_by_id  
( 
	IN _id_actions BIGINT
) RETURNS void AS $$
BEGIN
	delete from actions 
			where id_actions = _id_actions;
	perform d_b_rha_by_actions_id(_id_actions);
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- baja de users_has_roles
-- ----------------------------------------
DROP FUNCTION IF EXISTS d_b_uhr_by_id;
CREATE FUNCTION d_b_uhr_by_id  
( 
	IN _id_users_has_roles BIGINT
) RETURNS void AS $$
BEGIN
  delete from users_has_roles 
		where id_users_has_roles = _id_users_has_roles;
END; 
$$ LANGUAGE plpgsql;
-- --------------------------------------------------------------
DROP FUNCTION IF EXISTS d_b_uhr_by_user_id;
CREATE FUNCTION d_b_uhr_by_user_id  
( 
	IN _users_id BIGINT
) RETURNS void AS $$
BEGIN
  delete from users_has_roles 
		where users_id = _users_id;
END; 
$$ LANGUAGE plpgsql;
-- --------------------------------------------------------------
DROP FUNCTION IF EXISTS d_b_uhr_by_roles_id;
CREATE FUNCTION d_b_uhr_by_roles_id  
( 
	IN _roles_id BIGINT
) RETURNS void AS $$
BEGIN
  delete from users_has_roles 
		where roles_id = _roles_id;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- baja de roles_has_actions
-- ----------------------------------------
DROP FUNCTION IF EXISTS d_b_rha_by_id;
CREATE FUNCTION d_b_rha_by_id  
( 
	IN _id_roles_has_actions BIGINT
) RETURNS void AS $$
BEGIN
	delete from roles_has_actions 
		where id_roles_has_actions = _id_roles_has_actions;
END; 
$$ LANGUAGE plpgsql;
-- -------------------------------------------------------------
DROP FUNCTION IF EXISTS d_b_rha_by_roles_id;
CREATE FUNCTION d_b_rha_by_roles_id 
( 
	IN _roles_id BIGINT
) RETURNS void AS $$
BEGIN
	delete from roles_has_actions 
		where roles_id = _roles_id;
END; 
$$ LANGUAGE plpgsql;
-- --------------------------------------------------------------
DROP FUNCTION IF EXISTS d_b_rha_by_actions_id;
CREATE FUNCTION d_b_rha_by_actions_id  
( 
	IN _actions_id BIGINT
) RETURNS void AS $$
BEGIN
  delete from roles_has_actions 
		where actions_id = _actions_id;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- -----------------------------------------------------------------

-- ----------------------------------------
-- Modificacion de user
-- ----------------------------------------
DROP FUNCTION IF EXISTS u_user_by_id;
CREATE FUNCTION u_user_by_id 
( 
	IN _id_users BIGINT,
	IN _identifier VARCHAR(256),
	IN _password_hash VARCHAR(256) 
) RETURNS void AS $$
BEGIN
  update users 
  	set identifier = _identifier,
  		password_hash = _password_hash
  	where id_users = _id_users;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------------
DROP FUNCTION IF EXISTS u_user_identifier_by_id;
CREATE FUNCTION u_user_identifier_by_id 
( 
	IN _id_users BIGINT,
	IN _identifier VARCHAR(256)
) RETURNS void AS $$
BEGIN
  update users 
  	set identifier = _identifier
  	where id_users = _id_users;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------------
DROP FUNCTION IF EXISTS u_user_pwd_hash_by_id;
CREATE FUNCTION u_user_pwd_hash_by_id 
( 
	IN _id_users BIGINT,
	IN _password_hash VARCHAR(256)
) RETURNS void AS $$
BEGIN
  update users 
  	set password_hash = _password_hash
  	where id_users = _id_users;
END; 
$$ LANGUAGE plpgsql;
-- -------------------------------------------------------
DROP FUNCTION IF EXISTS u_user_by_identifier;
CREATE FUNCTION u_user_by_identifier  
( 
	IN _identifier VARCHAR(256),
	IN _new_identifier VARCHAR(256),
	IN _password_hash VARCHAR(256) 
) RETURNS void AS $$
BEGIN
  update users 
  	set identifier = _new_identifier,
  		password_hash = _password_hash
  	where identifier = _identifier;
END; 
$$ LANGUAGE plpgsql;
-- -------------------------------------------------------
DROP FUNCTION IF EXISTS u_user_identifier_by_identifier;
CREATE FUNCTION u_user_identifier_by_identifier  
( 
	IN _identifier VARCHAR(256),
	IN _new_identifier VARCHAR(256)
) RETURNS void AS $$
BEGIN
  update users 
  	set identifier = _new_identifier
  	where identifier = _identifier;
END; 
$$ LANGUAGE plpgsql;
-- -------------------------------------------------------
DROP FUNCTION IF EXISTS u_user_pwd_hash_by_identifier;
CREATE FUNCTION u_user_pwd_hash_by_identifier
( 
	IN _identifier VARCHAR(256),
	IN _password_hash VARCHAR(256) 
) RETURNS void AS $$
BEGIN
  update users 
  	set password_hash = _password_hash
  	where identifier = _identifier;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Modificacion de roles
-- ----------------------------------------
DROP FUNCTION IF EXISTS u_rol_by_id;
CREATE FUNCTION u_rol_by_id
( 
	IN _id_roles BIGINT,
	IN _name VARCHAR(256),
	IN _description VARCHAR(256) 
) RETURNS void AS $$
BEGIN
  update roles
  	set name = _name,
   		description = _description
  	where id_roles = _id_roles;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------------
DROP FUNCTION IF EXISTS u_rol_name_by_id;
CREATE FUNCTION u_rol_name_by_id
( 
	IN _id_roles BIGINT,
	IN _name VARCHAR(256)
) RETURNS void AS $$
BEGIN
  update roles
  	set name = _name
  	where id_roles = _id_roles;
END; 
$$ LANGUAGE plpgsql;
-- -----------------------------------------------
DROP FUNCTION IF EXISTS u_rol_description_by_id;
CREATE FUNCTION u_rol_description_by_id
( 
	IN _id_roles BIGINT,
	IN _description VARCHAR(256) 
) RETURNS void AS $$
BEGIN
  update roles
  	set description = _description
  	where id_roles = _id_roles;
END; 
$$ LANGUAGE plpgsql;
-- ---------------------------------------------------
DROP FUNCTION IF EXISTS u_rol_by_name;
CREATE FUNCTION u_rol_by_name
( 
	IN _name VARCHAR(256),
	IN _new_name VARCHAR(256),
	IN _description VARCHAR(256) 
) RETURNS void AS $$
BEGIN
  update roles
  	set name = _new_name,
   		description = _description
  	where name = _name;
END; 
$$ LANGUAGE plpgsql;
-- ---------------------------------------------------
DROP FUNCTION IF EXISTS u_rol_name_by_name;
CREATE FUNCTION u_rol_name_by_name
( 
	IN _name VARCHAR(256),
	IN _new_name VARCHAR(256)
) RETURNS void AS $$
BEGIN
  update roles
  	set name = _new_name
  	where name = _name;
END; 
$$ LANGUAGE plpgsql;
-- ---------------------------------------------------
DROP FUNCTION IF EXISTS u_rol_description_by_name;
CREATE FUNCTION u_rol_description_by_name
( 
	IN _name VARCHAR(256),
	IN _description VARCHAR(256) 
) RETURNS void AS $$
BEGIN
  update roles
  	set description = _description
  	where name = _name;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- Modificacion de action
-- ----------------------------------------
DROP FUNCTION IF EXISTS u_action_by_id;
CREATE FUNCTION u_action_by_id
( 
	IN _id_actions BIGINT,
	IN _name VARCHAR(256)
) RETURNS void AS $$
BEGIN
  update actions 
  	set name = _name
  	where id_actions = _id_actions;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
DROP FUNCTION IF EXISTS u_action_by_name;
CREATE FUNCTION u_action_by_name
( 
	IN _name VARCHAR(256),
	IN _new_name VARCHAR(256)
) RETURNS void AS $$
BEGIN
  update actions 
  	set name = _new_name
  	where name = _name;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- modificar users_has_roles
-- ----------------------------------------
DROP FUNCTION IF EXISTS u_b_uhr_by_id;
CREATE FUNCTION u_b_uhr_by_id
( 
	IN _id_users_has_roles BIGINT,
	IN _users_id BIGINT,
	IN _roles_id BIGINT
) RETURNS void AS $$
BEGIN
  update users_has_roles
  	set users_id = _users_id,
  		roles_id = _roles_id
  	where id_actions = _id_actions;
END; 
$$ LANGUAGE plpgsql;
-- --------------------------------------------------------
DROP FUNCTION IF EXISTS u_b_uhr_user_id_by_id;
CREATE FUNCTION u_b_uhr_user_id_by_id
( 
	IN _id_users_has_roles BIGINT,
	IN _users_id BIGINT
) RETURNS void AS $$
BEGIN
  update users_has_roles
  	set users_id = _users_id
  	where id_actions = _id_actions;
END; 
$$ LANGUAGE plpgsql;
-- --------------------------------------------------------
DROP FUNCTION IF EXISTS u_b_uhr_rol_id_by_id;
CREATE FUNCTION u_b_uhr_rol_id_by_id
( 
	IN _id_users_has_roles BIGINT,
	IN _roles_id BIGINT
) RETURNS void AS $$
BEGIN
  update users_has_roles
  	set roles_id = _roles_id
  	where id_actions = _id_actions;
END; 
$$ LANGUAGE plpgsql;
-- ------------------------------------------------------------
DROP FUNCTION IF EXISTS u_b_uhr_user_id_by_user_id;
CREATE FUNCTION u_b_uhr_user_id_by_user_id
( 
	IN _users_id BIGINT,
	IN _new_user_id BIGINT
) RETURNS void AS $$
BEGIN
  update users_has_roles
  	set users_id = _new_user_id
  	where users_id = _users_id;
END; 
$$ LANGUAGE plpgsql;
-- ------------------------------------------------------------
DROP FUNCTION IF EXISTS u_b_uhr_rol_id_by_rol_id;
CREATE FUNCTION u_b_uhr_rol_id_by_rol_id
( 
	IN _roles_id BIGINT,
	IN _new_roles_id BIGINT
) RETURNS void AS $$
BEGIN
  update users_has_roles
  	set roles_id = _new_roles_id
  	where roles_id = _roles_id;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------

-- ----------------------------------------
-- modificar roles_has_actions
-- ----------------------------------------
DROP FUNCTION IF EXISTS u_b_rha_by_id;
CREATE FUNCTION u_b_rha_by_id
( 
	IN _id_roles_has_actions BIGINT,
	IN _roles_id BIGINT,
	IN _actions_id BIGINT	
) RETURNS void AS $$
BEGIN
  update roles_has_actions
  	set roles_id = _roles_id,
  		actions = _actions_id
  	where id_roles_has_actions = _id_roles_has_actions;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------------------------
DROP FUNCTION IF EXISTS u_b_rha_rol_id_by_id;
CREATE FUNCTION u_b_rha_rol_id_by_id
( 
	IN _id_roles_has_actions BIGINT,
	IN _roles_id BIGINT
) RETURNS void AS $$
BEGIN
  update roles_has_actions
  	set roles_id = _roles_id
  	where id_roles_has_actions = _id_roles_has_actions;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------------------------
DROP FUNCTION IF EXISTS u_b_rha_action_id_by_id;
CREATE FUNCTION u_b_rha_action_id_by_id
( 
	IN _id_roles_has_actions BIGINT,
	IN _actions_id BIGINT
) RETURNS void AS $$
BEGIN
  update roles_has_actions
  	set actions_id = _actions_id
  	where id_roles_has_actions = _id_roles_has_actions;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------------------------
DROP FUNCTION IF EXISTS u_b_rha_rol_id_by_rol_id;
CREATE FUNCTION u_b_rha_rol_id_by_rol_id
( 
	IN _roles_id BIGINT,
	IN _new_roles_id BIGINT
) RETURNS void AS $$
BEGIN
  update roles_has_actions
  	set roles_id = _new_roles_id
  	where roles_id = _roles_id;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------------------------
DROP FUNCTION IF EXISTS u_b_rha_action_id_by_action_id;
CREATE FUNCTION u_b_rha_action_id_by_action_id
( 
	IN _actions_id BIGINT,
	IN _new_actions_id BIGINT	
) RETURNS void AS $$
BEGIN
  update roles_has_actions
  	set actions = _new_actions_id
  	where actions_id = _actions_id;
END; 
$$ LANGUAGE plpgsql;
-- ----------------------------------------
-- ----------------------------------------


-- ---------------------------------------------

-- Obtener PK de users_has_roles con las FK de users y roles $$
DROP FUNCTION IF EXISTS get_uhr_id_by_fks;
CREATE FUNCTION get_uhr_id_by_fks  
(
	IN _users_id BIGINT,
	IN _roles_id BIGINT
) RETURNS void AS $$
BEGIN
	select id_users_has_roles 
	from users_has_roles
	where users_id = _users_id
	and roles_id = _roles_id
	limit 1; 
END; 
$$ LANGUAGE plpgsql;

-- Obtener PK de roles_has_actions con las FK de roles y actions $$
DROP FUNCTION IF EXISTS get_rha_id_by_fks;
CREATE FUNCTION get_rha_id_by_fks  
(
	IN _roles_id BIGINT,
	IN _actions_id BIGINT
) RETURNS void AS $$
BEGIN
	select id_roles_has_actions 
	from roles_has_actions
	where actions_id = _actions_id
	and roles_id = _roles_id
	limit 1; 
END; 
$$ LANGUAGE plpgsql;

-- Obtener PK de users a partir de identifier $$
DROP FUNCTION IF EXISTS get_id_users;
CREATE FUNCTION get_id_users  
(
	IN _identifier BIGINT
) RETURNS void AS $$
BEGIN
	select id_users 
	from users 
	where identifier = _identifier
	limit 1;
END; 
$$ LANGUAGE plpgsql;

-- Obtener PK de roles a partir de name $$
DROP FUNCTION IF EXISTS get_id_roles;
CREATE FUNCTION get_id_roles  
(
	IN _name BIGINT
) RETURNS void AS $$
BEGIN
	select id_roles 
	from roles 
	where name = _name
	limit 1;
END; 
$$ LANGUAGE plpgsql;

-- Obtener PK de actions a partir de name $$
DROP FUNCTION IF EXISTS get_id_actions;
CREATE FUNCTION get_id_actions  
(
	IN _name BIGINT
) RETURNS void AS $$
BEGIN
	select id_actions 
	from actions 
	where name = _name
	limit 1;
END; 
$$ LANGUAGE plpgsql;

-- ---------------------------------------------------------------------
-- obtener los datos que estan relacionados entre users, roles y actions
-- ---------------------------------------------------------------------
DROP FUNCTION IF EXISTS get_all_common;
CREATE FUNCTION get_all_common() RETURNS void AS $$
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
END; 
$$ LANGUAGE plpgsql;

