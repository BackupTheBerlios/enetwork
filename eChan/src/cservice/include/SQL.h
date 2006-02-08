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

#ifndef ELECTRONIC_NETWORKS__CSERVICE_SQL_H
#define ELECTRONIC_NETWORKS__CSERVICE_SQL_H

#include <string>
#include <mysql++.h>

#include "SqlUser.h"
#include "SqlChannel.h"
// #include "SqlChannelAccess.h"
#include "Cache.h"
#include "Client.h"
#include "Channel.h"
#include "SqlManager.h"

namespace eNetworks
{

namespace cservice
{

class SQL
{
   public:
   	// TODO: Get these values from configuration file.
   	SQL() : M_UserCache(50, 10000), M_ChannelCache(50, 10000)
   	{}

   	typedef Cache<unsigned int, SqlUser> UserCache;
   	typedef Cache<unsigned int, SqlChannel> ChannelCache;
//   	bool HasEnoughAccess(const std::string& username, const std::string& channel, unsigned int level);
   	
   	SqlUser* FindUser(Client* p_Client);
//   	SqlUser FindUser(const std::string& username);

//   	SqlChannel FindChannel(Channel* p_Channel);
//   	SqlChannel FindChannel(const std::string& channel);

   	SqlUser* login(const std::string& username, const std::string& password);

   	static SQL Interface;

   private:
//   	typedef Cache<unsigned int, ChannelAccess> ChannelAccesCache;

   	// Have to return a pointer because Result destruct members not sure why.
   	bool QueryDB(const std::string& table, const std::string& variables, const std::string values, mysqlpp::Result& p_result);

   	UserCache M_UserCache;
   	ChannelCache M_ChannelCache;

};

} // namespace cservice

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__CSERVICE_SQL_H
