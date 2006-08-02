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

#include <utility>
#include <string>
#include <mysql++.h>
#include <iostream>

#include "SqlUser.h"
#include "SqlChannel.h"
#include "SqlChannelAccess.h"
#include "Cache.h"
#include "Client.h"
#include "Channel.h"
#include "SqlManager.h"
#include "MsgTokenizer.h"

namespace eNetworks
{

namespace cservice
{

class SQL
{
   public:
   	typedef Cache<unsigned int, SqlUser> UserCache;
   	typedef Cache<unsigned int, SqlChannel> ChannelCache;
   	typedef Cache<unsigned int, SqlChannelAccess> ChannelAccessCache;

   	// TODO: Get these values from configuration file.
   	SQL() : M_UserCache(50, 10000), M_ChannelCache(50, 10000), M_ChannelAccessCache(50, 10000)
   	{}

   	unsigned short GetAccessLevel(const unsigned int& username_id, const unsigned int& channel_id);
   	unsigned short GetAccessLevel(const std::string& username, const std::string& channel);

   	unsigned short GetAccessLevel(Client* p_Client, Channel* p_Channel);

   	unsigned short GetAccessLevel(const std::string& username, Channel* p_Channel)
   	{
   	   if (NULL == p_Channel)
   	   	return 0;

   	   return GetAccessLevel(username, p_Channel->GetName());
   	}

   	SqlChannelAccess* FindChannelAccess(const unsigned int& id);
   	SqlChannelAccess* FindChannelAccess(const unsigned int& username_id, const unsigned int& channel_id);
   	SqlChannelAccess* FindChannelAccess(const unsigned int& username_id, const std::string& channel)
   	{
   	   SqlChannel* l_SqlChannel = FindChannel(channel);
   	   if (NULL == l_SqlChannel)
   	   	return NULL;

   	   return FindChannelAccess(username_id, l_SqlChannel->getID());
   	}

   	unsigned short GetAccessLevel(const unsigned int& id);

   	unsigned short GetAccessLevel(Client* p_Client, const unsigned int& channel_id);

   	unsigned short GetAccessLevel(Client* p_Client, const std::string& channel)
   	{
   	   SqlChannel* l_SqlChannel = FindChannel(channel);
   	   if (NULL == l_SqlChannel)
   	   	return 0;

   	   return GetAccessLevel(p_Client, l_SqlChannel->getID());
   	}

   	bool HasEnoughAccess(Client* p_Client, Channel* p_Channel, const unsigned int& level)
   	{
   	   return (GetAccessLevel(p_Client, p_Channel) >= level);
   	}

   	bool HasEnoughAccess(const std::string& username, const std::string& channel, const unsigned int& level)
   	{
   	   return (GetAccessLevel(username, channel) >= level);
   	}

   	bool HasEnoughAccess(Client* p_Client, const std::string& channel, const unsigned int& level)
   	{
   	   return (GetAccessLevel(p_Client, channel) >= level);
   	}

   	bool HasEnoughAccess(const std::string& username, Channel* p_Channel, const unsigned int& level)
   	{
   	   return (GetAccessLevel(username, p_Channel) >= level);
   	}

   	// These return pointers that are stored in the Cache.
   	// Don't expect these to be in memory for very long.
   	SqlUser* FindUser(const unsigned int& username_id);
   	SqlUser* FindUser(const std::string& username);
   	SqlUser* FindUser(Client* p_Client)
   	{
   	   // Make sure we don't get a NULL pointer.
   	   if (NULL == p_Client)
   	   	return NULL;

   	   // If the user is not logged he/she will not have an ID set.
   	   if (!p_Client->IsLogged())
   	   	return NULL;

   	   return FindUser(static_cast<unsigned int>(p_Client->GetID()));
   	}

   	SqlChannel* FindChannel(const unsigned int& channel_id);
   	SqlChannel* FindChannel(const std::string& channel);
   	SqlChannel* FindChannel(Channel* p_Channel)
   	{
   	   if (NULL == p_Channel)
   	   	return NULL;

   	   return FindChannel(p_Channel->GetName());
   	}

   	SqlUser* login(const std::string& username, const std::string& password);

   	static SQL Interface;

   	void CacheInsert(const SqlUser& user)
   	{
   	   M_UserCache.insert(UserCache::value_type(user.getID(), user));
   	}

   	void CacheDelete(const SqlUser& user)
   	{
   	   M_UserCache.erase(user.getID());

/*   	   UserCache::iterator Iter = M_UserCache.find(user.getID());
   	   if (Iter != M_UserCache.end())
   	   	M_UserCache.erase(Iter);
*/
   	}
  	void CacheInsert(const SqlChannel& channel)
   	{
   	   M_ChannelCache.insert(ChannelCache::value_type(channel.getID(), channel));
   	}

   	void CacheDelete(const SqlChannel& channel)
   	{
   	   M_ChannelCache.erase(channel.getID());
   	}

   	void CacheInsert(const SqlChannelAccess& channelaccess)
   	{
   	   M_ChannelAccessCache.insert(ChannelAccessCache::value_type(channelaccess.getID(), channelaccess));
   	}

   	void CacheDelete(const SqlChannelAccess& channelaccess)
   	{
   	   M_ChannelAccessCache.erase(channelaccess.getID());
   	}

   private:
//   	bool QueryDB(const std::string& table, const MsgTokenizer& variables, const MsgTokenizer& values, mysqlpp::Result& p_result);
//   	unsigned int InsertDB(const std::string& table, const MsgTokenizer& variables, const MsgTokenizer& values);

   	UserCache M_UserCache;
   	ChannelCache M_ChannelCache;
   	ChannelAccessCache M_ChannelAccessCache;
};

} // namespace cservice

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__CSERVICE_SQL_H
