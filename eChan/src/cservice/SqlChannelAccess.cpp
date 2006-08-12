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
#include "SqlChannelAccess.h"
#include "SQL.h"
#include "SqlManager.h"
#include "tools.h"

using std::string;

namespace eNetworks
{

namespace cservice
{

void SqlChannelAccess::update()
{
   string l_variables = "username_id channel_id level automode";
   string l_values = IntToString(M_username_id);
   l_values += " " + IntToString(M_channel_id);
   l_values += " " + IntToString(M_level);
   l_values += " " + IntToString(M_automode);

   if (M_id == 0)
   {

   	SqlManager::InsertDB("SqlChannelAccess", l_variables, l_values);
   	SQL::Interface.CacheInsert(*this);
   }
   else
   {
   	SqlManager::UpdateDB("SqlChannelAccess", l_variables, l_values, M_id);
   }
}

void SqlChannelAccess::Delete()
{
   // if M_id == 0 only delete from UserCache
   if (M_id != 0)
   {
   	SqlManager::DeleteDB("SqlChannelAccess", M_id);
   }

   SQL::Interface.CacheDelete(*this);
}

} // namespace cservice

} // namespace eNetworks
