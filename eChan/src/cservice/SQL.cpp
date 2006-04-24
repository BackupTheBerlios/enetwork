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

#include <mysql++.h>
#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include "debug.h"
#include "SQL.h"
#include "SqlUser.h"
#include "SqlManager.h"
#include "Crypto.h"
#include "Client.h"
#include "MsgTokenizer.h"
#include "tools.h"
#include "ConfigParser.h"

using mysqlpp::Connection;
using mysqlpp::Query;
using mysqlpp::Result;
using mysqlpp::Exception;
using mysqlpp::BadQuery;
using mysqlpp::Row;
using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

namespace cservice
{

SqlUser* SQL::login(const std::string& username, const std::string& password)
{
   // Check if user is in cache.
   for (UserCache::iterator l_Iter = M_UserCache.begin(); l_Iter != M_UserCache.end(); l_Iter++)
   {
   	// User is in cache.
   	if (StringCaseCompare(l_Iter->second.getUsername(),username))
   	{
   	   // Check for password. If password doesn't match maybe password was 
   	   // updated from webpage or somewhere else. If that's the case go to database.
   	   if (Crypto::MatchPassword(password, l_Iter->second.getPassword()))
   	   {
   	   	return &l_Iter->second;
   	   }
   	}
   }

   Result l_result;
   SqlManager::QueryDB("SqlUser", string("SqlUser.username"), username, l_result);
   if (l_result.rows() == 1)
   {
        Row l_row = l_result.fetch_row();
        if (Crypto::MatchPassword(password, l_row["password"].get_string() ))
        {
           // Check if the user is still in cache from previous login.
   	   // If it is then set its new password.
           UserCache::iterator l_Iter = M_UserCache.find(l_row["id"]);
   	   if (M_UserCache.end() != l_Iter)
   	   {
   	   	l_Iter->second.setPassword(l_row["password"].get_string());
   	   }
   	   else
   	   {
   	   	SqlUser l_SqlUser(l_row["id"], l_row["username"].get_string(), l_row["password"].get_string(),
   	   	   	   	  l_row["email"].get_string());
           	M_UserCache.insert( SQL::UserCache::value_type(l_SqlUser.getID(), l_SqlUser) );
   	   	l_Iter = M_UserCache.find(l_SqlUser.getID());
   	   }

   	   return &l_Iter->second;
        }
   }

   return NULL;
}

SqlUser* SQL::FindUser(const unsigned int& username_id)
{
   // Is it cached?
   UserCache::iterator l_Iter = M_UserCache.find(username_id);
   if(M_UserCache.end() != l_Iter)
   	return &l_Iter->second;

   // not cached. Query database.
   Result l_result;
   SqlManager::QueryDB("SqlUser", string("SqlUser.id"), IntToString(username_id), l_result);

   // Found a match on database.
   if (l_result.rows() == 1)
   {
        Row l_row = l_result.fetch_row();
        SqlUser l_SqlUser(l_row["id"], l_row["username"].get_string(), l_row["password"].get_string(),
                            l_row["email"].get_string());

        M_UserCache.insert(SQL::UserCache::value_type(l_SqlUser.getID(), l_SqlUser));
        return &M_UserCache.find(username_id)->second;
   }

   return NULL;
}

SqlUser* SQL::FindUser(const std::string& username)
{
   // Check if user is in cache.
   for (UserCache::iterator l_Iter = M_UserCache.begin(); l_Iter != M_UserCache.end(); l_Iter++)
        if (StringCaseCompare(l_Iter->second.getUsername(), username))
             return &l_Iter->second;

   Result l_result;
   SqlManager::QueryDB("SqlUser", string("SqlUser.username"), username, l_result);
   if (l_result.rows() == 1)
   {
        Row l_row = l_result.fetch_row();
        SqlUser l_SqlUser(l_row["id"], l_row["username"].get_string(), l_row["password"].get_string(),
                          l_row["email"].get_string());

        M_UserCache.insert(SQL::UserCache::value_type(l_SqlUser.getID(), l_SqlUser));
        return &M_UserCache.find(l_SqlUser.getID())->second;
   }

   return NULL;
}

SqlChannel* SQL::FindChannel(const unsigned int& channel_id)
{
   ChannelCache::iterator l_Iter = M_ChannelCache.find(channel_id);

   if (l_Iter != M_ChannelCache.end())
   	return &l_Iter->second;

   Result l_result;
   SqlManager::QueryDB("SqlChannel", string("SqlChannel.id"), IntToString(channel_id), l_result);
   if (l_result.rows() == 1)
   {
   	Row l_row = l_result.fetch_row();
   	SqlChannel l_SqlChannel(l_row["id"], l_row["name"].get_string(), l_row["description"].get_string(),
   	   	   	   	l_row["homepage"].get_string());

   	M_ChannelCache.insert(ChannelCache::value_type(channel_id, l_SqlChannel));
   	return &M_ChannelCache.find(channel_id)->second;
   }

   return NULL;
}

SqlChannel* SQL::FindChannel(const std::string& channel)
{
   // Check cached for cached SqlChannels.
   for (ChannelCache::iterator l_Iter = M_ChannelCache.begin(); l_Iter != M_ChannelCache.end(); l_Iter++)
   {
   	if (StringCaseCompare(l_Iter->second.getName(), channel))
   	   return &l_Iter->second;
   }

   Result l_result;
   SqlManager::QueryDB("SqlChannel", string("SqlChannel.name"), channel, l_result);
   if (l_result.rows() == 1)
   {
        Row l_row = l_result.fetch_row();
        SqlChannel l_SqlChannel(l_row["id"], l_row["name"].get_string(), l_row["description"].get_string(),
                                l_row["homepage"].get_string());

        M_ChannelCache.insert(ChannelCache::value_type(l_SqlChannel.getID(), l_SqlChannel));
        return &M_ChannelCache.find(l_SqlChannel.getID())->second;
   }

   return NULL;
}

SqlChannelAccess* SQL::FindChannelAccess(const unsigned int& id)
{
   ChannelAccessCache::iterator l_Iter = M_ChannelAccessCache.find(id);
   if (l_Iter != M_ChannelAccessCache.end())
        return &l_Iter->second;

   Result l_result;
   SqlManager::QueryDB("SqlChannelAccess", string("id"), IntToString(id), l_result);

   if (l_result.rows() > 0)
   {
        if (l_result.rows() != 1)
        {
           debug << "SqlChannelAccess: Found multiple channel access for some username_id on different channel_id" << endb;
           return 0;
        }

        Row l_row = l_result.fetch_row();
        SqlChannelAccess l_ChannelAccess(l_row["id"], l_row["username_id"], l_row["channel_id"], l_row["level"]);
        M_ChannelAccessCache.insert(ChannelAccessCache::value_type(l_row["id"], l_ChannelAccess));

        return &M_ChannelAccessCache.find(id)->second;
   }

   return NULL;
}

SqlChannelAccess* SQL::FindChannelAccess(const unsigned int& username_id, const unsigned int& channel_id)
{
   for(ChannelAccessCache::iterator l_Iter = M_ChannelAccessCache.begin(); l_Iter != M_ChannelAccessCache.end(); ++l_Iter)
   {
        if (l_Iter->second.getUsernameID() == username_id && l_Iter->second.getChannelID() == channel_id)
           return &l_Iter->second;
   }

   Result l_result;
   SqlManager::QueryDB("SqlChannelAccess", string("username_id channel_id"), IntToString(username_id) + " " + IntToString(channel_id), l_result);

   if (l_result.rows() > 0)
   {
        if (l_result.rows() != 1)
        {
           debug << "SqlChannelAccess: Found multiple channel access for some username_id on different channel_id" << endb;
           return 0;
        }

        Row l_row = l_result.fetch_row();
        SqlChannelAccess l_ChannelAccess(l_row["id"], username_id, channel_id, l_row["level"]);
        M_ChannelAccessCache.insert(ChannelAccessCache::value_type(l_row["id"], l_ChannelAccess));

        return &M_ChannelAccessCache.find(l_row["id"])->second;
   }

   return NULL;
}

unsigned short SQL::GetAccessLevel(const unsigned int& id)
{
   ChannelAccessCache::iterator l_Iter = M_ChannelAccessCache.find(id);
   if (l_Iter != M_ChannelAccessCache.end())
   	return l_Iter->second.getLevel();

   Result l_result;
   SqlManager::QueryDB("SqlChannelAccess", string("id"), IntToString(id), l_result);

   if (l_result.rows() > 0)
   {
        if (l_result.rows() != 1)
        {
           debug << "SqlChannelAccess: Found multiple channel access for some username_id on different channel_id" << endb;
           return 0;
        }

        Row l_row = l_result.fetch_row();
        SqlChannelAccess l_ChannelAccess(l_row["id"], l_row["username_id"], l_row["channel_id"], l_row["level"]);
        M_ChannelAccessCache.insert(ChannelAccessCache::value_type(l_row["id"], l_ChannelAccess));

        return l_ChannelAccess.getLevel();
   }

   return 0;
}

unsigned short SQL::GetAccessLevel(const unsigned int& username_id, const unsigned int& channel_id)
{
   for(ChannelAccessCache::iterator l_Iter = M_ChannelAccessCache.begin(); l_Iter != M_ChannelAccessCache.end(); ++l_Iter)
   {
   	if (l_Iter->second.getUsernameID() == username_id && l_Iter->second.getChannelID() == channel_id)
   	   return l_Iter->second.getLevel();
   }

   Result l_result;
   SqlManager::QueryDB("SqlChannelAccess", string("username_id channel_id"), IntToString(username_id) + " " + IntToString(channel_id), l_result);

   if (l_result.rows() > 0)
   {
   	if (l_result.rows() != 1)
   	{
   	   debug << "SqlChannelAccess: Found multiple channel access for some username_id on different channel_id" << endb;
   	   return 0;
   	}

   	Row l_row = l_result.fetch_row();
   	SqlChannelAccess l_ChannelAccess(l_row["id"], username_id, channel_id, l_row["level"]);
   	M_ChannelAccessCache.insert(ChannelAccessCache::value_type(l_row["id"], l_ChannelAccess));

   	return l_ChannelAccess.getLevel();
   }

   return 0;
}

unsigned short SQL::GetAccessLevel(const std::string& username, const std::string& channel)
{
   SqlUser* l_SqlUser = FindUser(username);
   SqlChannel* l_SqlChannel = FindChannel(channel);

   if (NULL == l_SqlUser || NULL == l_SqlChannel)
   	return 0;

   return GetAccessLevel(l_SqlUser->getID(), l_SqlChannel->getID());
}

unsigned short SQL::GetAccessLevel(Client* p_Client, Channel* p_Channel)
{
   if (NULL == p_Client || NULL == p_Channel)
   	return 0;

    // If user hasn't logged in with us it has no id.
    if (!p_Client->IsLogged())
    {
        if (!p_Client->HasAccount())
           return 0;

        SqlUser* l_SqlUser = FindUser(p_Client->GetAccount());
        if (NULL == l_SqlUser)
           return 0;

        // Set user ID on client object.
        p_Client->SetID(static_cast<int>(l_SqlUser->getID()));
    }

    SqlChannel* l_SqlChannel = FindChannel(p_Channel->GetName());
    if (NULL == l_SqlChannel)
       return 0;

    return GetAccessLevel(p_Client->GetID(), l_SqlChannel->getID());
}

unsigned short SQL::GetAccessLevel(Client* p_Client, const unsigned int& channel_id)
{
   if (p_Client == NULL)
        return 0;

   // If user hasn't logged in with us it has no id.
   if (!p_Client->IsLogged())
   {
        if (!p_Client->HasAccount())
           return 0;

        SqlUser* l_SqlUser = FindUser(p_Client->GetAccount());
        if (NULL == l_SqlUser)
           return 0;

        // Set user ID on client object.
        p_Client->SetID(l_SqlUser->getID());
   }

   return GetAccessLevel(p_Client->GetID(), channel_id);
}

SQL SQL::Interface = SQL();

}

}
