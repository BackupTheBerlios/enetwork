/*
 * eChan - Electronic Channel Services.
 * Copyright (C) 2003-2005 Alan Alvarez.
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

namespace eNetworks
{

namespace cservice
{

struct SqlChannel
{
   	SqlChannel(const unsigned int& id, const std::string& name, std::string& description, 
  	   	   const std::string& homepage) : M_id(id), M_name(name), M_description(description),
  	   	   M_homepage(homepage)
   	{
   	}

   	SqlChannel() {}
   
   	unsigned int M_id;
   	std::string M_name;
   	std::string M_description;
   	std::string M_homepage;
};

} // namespace eNetworks

} // namespace cservice

#endif // ELECTRONIC_NETWORKS__CSERVICE_SQLCHANNEL_H
