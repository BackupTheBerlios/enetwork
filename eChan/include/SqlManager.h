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

#ifndef ELECTRONIC_NETWORKS__SQLMANAGER_H
#define ELECTRONIC_NETWORKS__SQLMANAGER_H

#include <mysql++.h>
#include <string>

#include "MsgTokenizer.h"

namespace eNetworks
{

class SqlManager
{
   public:
   	static void connect(const std::string& p_DB, const std::string& p_hostname, const std::string& p_username, const std::string& p_password);
   	static mysqlpp::Query query() { return SqlManager::M_Connection->query(); }
   	static bool QueryDB(const std::string& table, const MsgTokenizer& variables, const MsgTokenizer& values, mysqlpp::Result& p_result);
   	static unsigned int InsertDB(const std::string& table, const MsgTokenizer& variables, const MsgTokenizer& values);
   	static bool UpdateDB(const std::string& table, const MsgTokenizer& variables, const MsgTokenizer& values);

   private:
   	static mysqlpp::Connection* M_Connection;
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__SQLMANAGER_H
