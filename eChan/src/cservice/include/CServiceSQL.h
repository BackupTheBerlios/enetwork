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

#ifndef ELECTRONIC_NETWORKS__CSERVICE_CSERVICESQL_H
#define ELECTRONIC_NETWORKS__CSERVICE_CSERVICESQL_H

#include <mysql++/custom.h>

using namespace mysqlpp;

namespace eNetworks
{

namespace cservice
{
sql_create_3(SqlChannelAccess,
             1, 3,
             unsigned int, channelid,
             unsigned int, usernameid,
             unsigned int, level)


sql_create_4(SqlUser,
             1, 4,
             unsigned int, id,
             string, username,
             string, password,
             string, email)

sql_create_5(SqlChannel,
   	     1, 5,
   	     unsigned int, id,
   	     string, name,
   	     string, description,
   	     string, owner,
   	     string, homepage)

} // namespace eNetworks

} // namespace cservice

#endif // ELECTRONIC_NETWORKS__CSERVICE_CSERVICESQL_H
