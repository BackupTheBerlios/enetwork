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

#include <iostream>
#include <string>
#include <mysql++.h>

#include "MsgTokenizer.h"
#include "CommandLOGIN.h"
#include "Client.h"
#include "CServiceSQL.h"

using std::cout;
using std::endl;
using std::string;

using mysqlpp::Connection;
using mysqlpp::Query;
using mysqlpp::Result;

namespace eNetworks
{

namespace cservice
{

CommandLOGIN::CommandLOGIN(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Command(theBot, theSource, refParameters)
{
   Syntax = "/MSG " + LocalBot->theClient.GetNickName() + " login <username> <password>";
}

void CommandLOGIN::Parser()
{
   if (Parameters.size() != 2)
   {
   	LocalBot->SendNotice(Source, "SYNTAX: " + Syntax);
   	return;
   }

   Connection Conn("eChan", "localhost", "root", "mypass");

   if (!Conn.connected())
   {
   	LocalBot->SendNotice(Source, "Error: Cannot connect to database. Please contact a CService Administrator");
   	return;
   }

   Query query = Conn.query();
   query << "SELECT SqlUser.id FROM SqlUser WHERE SqlUser.username=%0q:username AND SqlUser.password=%1q:password";
   query.parse();

   query.def["username"] = Parameters[0];
   query.def["password"] = Parameters[1];

   cout << "Query: " << query.preview() << endl;

   Result result = query.store();

   if (result.size() != 1)
   {
   	LocalBot->SendNotice(Source, "Failed to login as " + Parameters[0] + ".");
   }
   else
   {
   	Source->SetAccount(Parameters[0]);
   	LocalBot->RawMsg(LocalBot->theClient.GetNumeric().substr(0,2) + " AC " + Source->GetNumeric() + " " + Parameters[0]);
   	LocalBot->SendNotice(Source, "You are now logged in as " + Parameters[0] + ".");
   }
}

} // namespace cservice

} // namespace eNetworks
