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
#include <utility>

#include "debug.h"
#include "SQL.h"
#include "SqlUser.h"
#include "SqlManager.h"
#include "Crypto.h"
#include "Client.h"
#include "MsgTokenizer.h"
#include "tools.h"

using mysqlpp::Connection;
using mysqlpp::Query;
using mysqlpp::Result;
using mysqlpp::Exception;
using mysqlpp::BadQuery;
using mysqlpp::Row;
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
   	if (l_Iter->second.getUsername() == username)
   	{
   	   // Check for password. If password doesn't match maybe password was 
   	   // updated from webpage or somewhere else. Go to database.
   	   if (Crypto::MatchPassword(password, l_Iter->second.getPassword()))
   	   {
   	   	return &l_Iter->second;
   	   }
   	}
   }

   Result l_result;
   QueryDB("SqlUser", "SqlUser.username", username, l_result);
   if (l_result.rows() == 1)
   {
        Row l_row = l_result.fetch_row();
        if (Crypto::MatchPassword(password, l_row["password"].get_string() ))
        {
           // Check if the user is still in cache from previous login.
   	   // If it is then pass new instance with new password to
   	   // the object's copy constructor.
           UserCache::iterator l_Iter = M_UserCache.find(l_row["id"]);
   	   if (M_UserCache.end() != l_Iter)
   	   {
   	   	l_Iter->second.setPassword(l_row["password"].get_string());
   	   }
   	   else
   	   {
   	   	SqlUser l_SqlUser(l_row["id"], l_row["username"].get_string(), l_row["password"].get_string(),
   	   	   	   	  l_row["email"].get_string());
           	M_UserCache.insert( SQL::UserCache::value_type(l_row["id"], l_SqlUser) );
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
   QueryDB("SqlUser", "SqlUser.id", IntToString(username_id), l_result);

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
        if (l_Iter->second.getUsername() == username)
             return &l_Iter->second;

   Result l_result;
   QueryDB("SqlUser", "SqlUser.username", username, l_result);
   if (l_result.rows() == 1)
   {
        Row l_row = l_result.fetch_row();
        SqlUser l_SqlUser(l_row["id"], l_row["username"].get_string(), l_row["password"].get_string(),
                          l_row["email"].get_string());

        M_UserCache.insert(SQL::UserCache::value_type(l_SqlUser.getID(), l_SqlUser));
        return &M_UserCache.find(l_row["id"])->second;
   }

   return NULL;
}

SqlChannel* SQL::FindChannel(const unsigned int& channel_id)
{
   ChannelCache::iterator l_Iter = M_ChannelCache.find(channel_id);

   if (l_Iter != M_ChannelCache.end())
   	return &l_Iter->second;

   Result l_result;
   QueryDB("SqlChannel", "SqlChannel.id", IntToString(channel_id), l_result);
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
   	if (l_Iter->second.getName() == channel)
   	   return &l_Iter->second;

   Result l_result;
   QueryDB("SqlChannel", "SqlChannel.name", channel, l_result);
   if (l_result.rows() == 1)
   {
        Row l_row = l_result.fetch_row();
        SqlChannel l_SqlChannel(l_row["id"], l_row["name"].get_string(), l_row["description"].get_string(),
                                l_row["homepage"].get_string());

        M_ChannelCache.insert(ChannelCache::value_type(l_row["id"], l_SqlChannel));
        return &M_ChannelCache.find(l_row["id"])->second;
   }

   return NULL;

}

bool SQL::QueryDB(const std::string& table, const std::string& variables, const std::string& values, Result& p_result)
{
   std::vector<std::pair<std::string, std::string> > l_VarsAndValues;
   MsgTokenizer l_TokenizedVars(variables);
   MsgTokenizer l_TokenizedValues(values);

   if (l_TokenizedVars.size() != l_TokenizedValues.size())
   	return false;

   Query l_query = SqlManager::query();
   l_query << "SELECT * FROM " << table << " WHERE";
   for (unsigned int i = 0; i < l_TokenizedVars.size(); i++)
   {
   	l_query << " " << l_TokenizedVars[i] << "=" << "%" << IntToString(i) << "q";
   	l_query.def[i] = l_TokenizedValues[i];
   	if (l_TokenizedVars.size() > 1 && i < (l_TokenizedVars.size() - 1))
   	   l_query << " AND";
   }
   l_query.parse();

   cout << "Query: " << l_query.preview() << endl;

   try
   {
        p_result = l_query.store();
   }
   catch(const BadQuery& e_error)
   {
        debug << "Query Error: " << e_error.what() << endb;
   	return false;
   }
   catch(const Exception& e_error)
   {
        debug << "Error: " << e_error.what() << endb;
   	return false;
   }

   return true;
}

unsigned short SQL::GetAccessLevel(const unsigned int& username_id, const unsigned int& channel_id)
{
   // Check for cache.
   ChannelAccessCache::iterator l_Iter = M_ChannelAccessCache.find(ChannelAccessCompare(username_id, channel_id));

   if (l_Iter != M_ChannelAccessCache.end())
   	return l_Iter->second.getLevel();

   Result l_result;
   QueryDB("SqlChannelAccess", "username_id channel_id", IntToString(username_id) + " " + IntToString(channel_id), l_result);

   if (l_result.rows() > 0)
   {
   	if (l_result.rows() != 1)
   	{
   	   debug << "SqlChannelAccess: Found multiple channel access for some username_id on different channel_id" << endb;
   	   return 0;
   	}

   	Row l_row = l_result.fetch_row();
   	SqlChannelAccess l_ChannelAccess(username_id, channel_id, l_row["level"]);
   	M_ChannelAccessCache.insert(ChannelAccessCache::value_type(ChannelAccessCompare(username_id, channel_id), l_ChannelAccess));

   	return l_ChannelAccess.getLevel();
   }

   return 0;
}

SQL SQL::Interface = SQL();

}

}
