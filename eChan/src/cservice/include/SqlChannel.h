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

#ifndef ELECTRONIC_NETWORKS__CSERVICE_SQLCHANNEL_H
#define ELECTRONIC_NETWORKS__CSERVICE_SQLCHANNEL_H

#include <string>

namespace eNetworks
{

namespace cservice
{

struct SqlChannel
{
   public:
   	SqlChannel(const unsigned int& id, const std::string& name, const std::string& description,
  	   	   const std::string& homepage) : 
        M_id(id), M_name(name), M_description(description), M_homepage(homepage)
   	{
   	}

   	SqlChannel() : M_id(0), M_name("NULL"), M_description("NULL"), M_homepage("NULL") {}

   	unsigned int getID() const { return M_id; }
   	std::string getName() const { return M_name; }
   	std::string getDescription() const { return M_description; }
   	std::string getHomepage() const { return M_homepage; }

   	void setID(const unsigned int&id)
   	{
   	   M_id = id;
   	}

   	void setName(const std::string& name)
   	{
   	   M_name = name;
   	}

   	void setDescription(const std::string& description)
   	{
   	   M_description = description;
   	}

   	void setHomepage(const std::string& homepage)
   	{
   	   M_homepage = homepage;
   	}

   	void update();

   private:
   	unsigned int M_id;
   	std::string M_name;
   	std::string M_description;
   	std::string M_homepage;
};

} // namespace eNetworks

} // namespace cservice

#endif // ELECTRONIC_NETWORKS__CSERVICE_SQLCHANNEL_H
