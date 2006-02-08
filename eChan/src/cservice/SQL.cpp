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
#include <vector>
#include <utility>

#include "debug.h"
#include "SQL.h"
#include "SqlUser.h"
#include "SqlManager.h"
#include "Crypto.h"
#include "Client.h"
#include "MsgTokenizer.h"

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
   Result l_result;
   QueryDB("SqlUser", "SqlUser.username", username, l_result);
   if (l_result.rows() == 1)
   {
        Row l_row = l_result.fetch_row();
        if (Crypto::MatchPassword(password, l_row["password"].get_string() ))
        {
   	   // Check if the user is still in cache from previous login.
   	   UserCache::iterator l_Iter = M_UserCache.find(l_row["id"]);
   	   if (M_UserCache.end() == l_Iter)
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

SqlUser* SQL::FindUser(Client* p_Client)
{
   // Make sure we don't get a NULL pointer.
   if (NULL == p_Client)
   	return NULL;

   // If the user is not logged he/she will not have an ID set.
   if (!p_Client->IsLogged())
   	return NULL;

   // Is it cached?
   UserCache::iterator l_Iter = M_UserCache.find(static_cast<unsigned int>(p_Client->GetID()));
   if(M_UserCache.end() != l_Iter)
   	return &l_Iter->second;

   // not cached. Query database.
   Result l_result;
   QueryDB("SqlUser", "SqlUser.id", IntToString(p_Client->GetID()), l_result);

   // Found a match on database.
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

bool SQL::QueryDB(const std::string& table, const std::string& variables, const std::string values, Result& p_result)
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

SQL SQL::Interface = SQL();

}

}
