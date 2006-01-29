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

#include <mysql++.h>
#include <iostream>

#include "debug.h"
#include "SQL.h"
#include "SqlUser.h"
#include "SqlManager.h"
#include "Crypto.h"

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
   Query query = SqlManager::query();
   query << "SELECT * FROM SqlUser WHERE SqlUser.username=%0q:username";
   query.parse();

   query.def["username"] = username;

   cout << "Query: " << query.preview() << endl;

   Result result;
   try
   {
        result = query.store();
   }
   catch(const BadQuery& e_error)
   {
        debug << "Query Error: " << e_error.what() << endb;
   	return NULL;
   }
   catch(const Exception& e_error)
   {
        debug << "Error: " << e_error.what() << endb;
   	return NULL;
   }

   if (result.rows() == 1)
   {
        Row l_row = result.fetch_row();
        if (Crypto::MatchPassword(password, l_row["password"].get_string() ))
        {
   	   // Check if the user is still in cache from previous login.
   	   UserCache::iterator l_Iter = M_UserCache.find(l_row["id"]);
   	   if (M_UserCache.end() == l_Iter)
   	   {
   	   	SqlUser l_SqlUser(l_row["id"], l_row["username"].get_string(), l_row["password"].get_string(),
   	   	   	     	  l_row["email"].get_string());

           	M_UserCache.insert(SQL::UserCache::value_type(l_row["id"], l_SqlUser));
   	   	l_Iter = M_UserCache.find(l_SqlUser.getID());
   	   }

   	   return &l_Iter->second;
        }
   }

   return NULL;
}

SqlUser* SQL::FindUser(const unsigned int& id)
{
   // Is it cached?
   UserCache::iterator l_Iter = M_UserCache.find(id);
   if(M_UserCache.end() != l_Iter)
   	return &l_Iter->second;

   // not cached. Query database.
   Query query = SqlManager::query();
   query << "SELECT * FROM SqlUser WHERE SqlUser.id=%0q:id";
   query.parse();

   query.def["id"] = id;

   cout << "Query: " << query.preview() << endl;

   Result result;
   try
   {
        result = query.store();
   }
   catch(const BadQuery& e_error)
   {
        debug << "Query Error: " << e_error.what() << endb;
   	return NULL;
   }
   catch(const Exception& e_error)
   {
        debug << "Error: " << e_error.what() << endb;
   	return NULL;
   }

   // Found a match on database.
   if (result.rows() == 1)
   {
        Row l_row = result.fetch_row();
        SqlUser l_SqlUser(l_row["id"], l_row["username"].get_string(), l_row["password"].get_string(),
                            l_row["email"].get_string());

        M_UserCache.insert(SQL::UserCache::value_type(l_SqlUser.getID(), l_SqlUser));
        return &M_UserCache.find(l_SqlUser.getID())->second;
   }

   return NULL;
}

SQL SQL::Interface = SQL();

}

}
