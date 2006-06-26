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

#include <string>
#include <iostream>
#include <mysql++.h>

#include "debug.h"
#include "SqlManager.h"
#include "MsgTokenizer.h"
#include "tools.h"

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

void SqlManager::connect(const string& p_DB, const string& p_hostname, const string& p_username, const string& p_password)
{
   SqlManager::M_Connection = new Connection(p_DB.c_str(), p_hostname.c_str(), p_username.c_str(), p_password.c_str());

   if (!M_Connection->connected())
   {
   	debug << "Cannot connect to database server." << endb;
   	exit(1);
   }
}

bool SqlManager::QueryDB(const std::string& table, const MsgTokenizer& variables, const MsgTokenizer& values, Result& p_result)
{
   if (variables.size() != values.size())
        return false;

   Query l_query = SqlManager::query();
   l_query << "SELECT * FROM " << table << " WHERE";
   for (unsigned int i = 0; i < variables.size(); i++)
   {
        l_query << " " << variables[i] << "=" << "%" << IntToString(i) << "q";
        l_query.def[i] = values[i];
        if (variables.size() > 1 && i < (variables.size() - 1))
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
        // Try to reconnect to database server.
        connect( ConfigFile.GetConfiguration("MYSQLDB"),
                 ConfigFile.GetConfiguration("MYSQLHOST"),
                 ConfigFile.GetConfiguration("MYSQLUSER"),
                 ConfigFile.GetConfiguration("MYSQLPASS") );

        // If we were to reconnect then we should be able to execute query now.
        // create a new query with new connection.
        Query l_copy = SqlManager::query();
        // copy old query string.
        l_copy << l_query.preview();
        // run the query.
        p_result = l_copy.store();
   }
   catch(const Exception& e_error)
   {
        debug << "Error: " << e_error.what() << endb;
        return false;
   }

   return true;
}

unsigned int SqlManager::InsertDB(const std::string& table, const MsgTokenizer& variables, const MsgTokenizer& values)
{
   if (variables.size() != values.size())
        return 0;

   Query l_query = SqlManager::query();
   l_query << "INSERT INTO " << table << " (" << variables.assamble(0, ',') << ") VALUES (";
   for (unsigned int i = 0; i < values.size(); i++)
   {
        l_query << "%" << IntToString(i) << "q";
        l_query.def[i] = values[i];
        if (values.size() > 1 && i < (values.size() - 1))
           l_query << ",";
   }

   l_query << ");";

   l_query.parse();

   cout << "Query: " << l_query.preview() << endl;

   try
   {
        return l_query.execute().insert_id;
   }
   catch(const BadQuery& e_error)
   {
        debug << "Query Error: " << e_error.what() << endb;
        // Try to reconnect to database server.
        connect( ConfigFile.GetConfiguration("MYSQLDB"),
                 ConfigFile.GetConfiguration("MYSQLHOST"),
                 ConfigFile.GetConfiguration("MYSQLUSER"),
                 ConfigFile.GetConfiguration("MYSQLPASS") );

        // If we were to reconnect then we should be able to execute query now.
        // create a new query with new connection.
        Query l_copy = query();
        // copy old query string.
        l_copy << l_query.preview();
        // run the query.
        l_copy.execute().insert_id;
   }
   catch(const Exception& e_error)
   {
        debug << "Error: " << e_error.what() << endb;
        return 0;
   }

/*
   // Get ID.
   Query l_queryID = query();
   l_queryID << "select LAST_INSERT_ID();";
   // We should have no problem this query.
   // Also connection should still be active.
   Result l_result = l_queryID.store();
   unsigned int l_RowsCount = l_result.rows();
   if (l_RowsCount > 0)
   {
   	Row l_row = l_result.fetch_row();
   	// Row[] operator doesn't take const unsigned ints.
   	unsigned int l_tmp = 0;
   	return l_row[l_tmp];
   }
*/
   return 0;
}

bool SqlManager::UpdateDB(const std::string& table, const MsgTokenizer& variables, const MsgTokenizer& values, const unsigned int& id)
{
   if (variables.size() != values.size())
        return 0;

   Query l_query = SqlManager::query();
   l_query << "UPDATE " << table << " SET ";
   for (unsigned int i = 0; i < values.size(); i++)
   {
   	l_query << variables[i] << " = ";
        l_query << "%" << IntToString(i) << "q";
        l_query.def[i] = values[i];
        if (values.size() > 1 && i < (values.size() - 1))
           l_query << ", ";
   }

   l_query << " WHERE id = " << id;

   l_query.parse();

   cout << "Query: " << l_query.preview() << endl;

   try
   {
        return l_query.execute();
   }
   catch(const BadQuery& e_error)
   {
        debug << "Query Error: " << e_error.what() << endb;
        // Try to reconnect to database server.
        connect( ConfigFile.GetConfiguration("MYSQLDB"),
                 ConfigFile.GetConfiguration("MYSQLHOST"),
                 ConfigFile.GetConfiguration("MYSQLUSER"),
                 ConfigFile.GetConfiguration("MYSQLPASS") );

        // If we were to reconnect then we should be able to execute query now.
        // create a new query with new connection.
        Query l_copy = query();
        // copy old query string.
        l_copy << l_query.preview();
        // run the query.
        return l_copy.execute();
   }
   catch(const Exception& e_error)
   {
        debug << "Error: " << e_error.what() << endb;
        return false;
   }
}


bool SqlManager::DeleteDB(const std::string& table, const MsgTokenizer& variables, const MsgTokenizer& values)
{
   Query l_query = SqlManager::query();
   l_query << "DELETE FROM " << table << " WHERE";
   for (unsigned int i = 0; i < variables.size(); i++)
   {
        l_query << " " << variables[i] << "=" << "%" << IntToString(i) << "q";
        l_query.def[i] = values[i];
        if (variables.size() > 1 && i < (variables.size() - 1))
           l_query << " AND";
   }
   l_query.parse();

   cout << "Query: " << l_query.preview() << endl;

  try
   {
        return l_query.execute();
   }
   catch(const BadQuery& e_error)
   {
        debug << "Query Error: " << e_error.what() << endb;
        // Try to reconnect to database server.
        connect( ConfigFile.GetConfiguration("MYSQLDB"),
                 ConfigFile.GetConfiguration("MYSQLHOST"),
                 ConfigFile.GetConfiguration("MYSQLUSER"),
                 ConfigFile.GetConfiguration("MYSQLPASS") );

        // If we were to reconnect then we should be able to execute query now.
        // create a new query with new connection.
        Query l_copy = query();
        // copy old query string.
        l_copy << l_query.preview();
        // run the query.
        return l_copy.execute();
   }
   catch(const Exception& e_error)
   {
        debug << "Error: " << e_error.what() << endb;
        return false;
   }
}

mysqlpp::Connection* SqlManager::M_Connection = NULL;

} // namespace eNetworks
