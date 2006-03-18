/*
 * eChan - Electronic Channel Services.
 * Copyright (C) 2003-2006 Alan Alvarez.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307,
 * USA.
 *
*/

#ifndef ELECTRONIC_NETWORKS__CSERVICE_SQLUSER_H
#define ELECTRONIC_NETWORKS__CSERVICE_SQLUSER_H

#include <string>
#include <iostream>

#include "SqlManager.h"

namespace eNetworks
{

namespace cservice
{

struct SqlUser
{
   public:
   	SqlUser(const unsigned int& id, const std::string& username,
   	   	const std::string& password, const std::string& email) :
   	   	M_id(id), M_username(username), M_password(password), M_email(email)
   	{}

   	SqlUser() : M_id(0), M_username("NULL"), M_password("NULL"), M_email("NULL")
   	{}

   	unsigned int getID() const { return M_id; }
   	std::string getUsername() const { return M_username; }
   	std::string getPassword() const { return M_password; }
   	std::string getEmail() const { return M_email; }

   	void setID(const unsigned int& id)
   	{
   	   M_id = id;
   	}

   	void setUsername(const std::string& username)
    	{
   	   M_username = username;
   	}

   	void setPassword(const std::string& password)
   	{
   	   M_password = password;
   	}

   	void setEmail(const std::string& email)
    	{
   	   M_email = email;
   	}

   	void update();

   private:
   	unsigned int M_id;
   	std::string M_username;
   	std::string M_password; // encrypted
   	std::string M_email;
};

} // namespace eNetworks

} // namespace cservice

#endif // ELECTRONIC_NETWORKS__CSERVICE_SQLUSER_H
