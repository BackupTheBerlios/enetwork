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
#include "SqlManager.h"
#include "Crypto.h"

using std::cout;
using std::endl;
using std::string;

using mysqlpp::Connection;
using mysqlpp::Query;
using mysqlpp::Result;
using mysqlpp::Exception;
using mysqlpp::BadQuery;

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

   if (Source->HasAccount())
   {
   	LocalBot->SendNotice(Source, "Sorry, you're already logged in as " + Source->GetAccount() + ".");
   	return;
   }
 
   Query query = SqlManager::query();
   query << "SELECT * FROM SqlUser WHERE SqlUser.username=%0q:username";
   query.parse();

   query.def["username"] = Parameters[0];

   cout << "Query: " << query.preview() << endl;

   Result result;
   try
   {
   	result = query.store();
   }
   catch(const BadQuery& e_error)
   {
   	cout << "Query Error: " << e_error.what() << endl;
   }
   catch(const Exception& e_error)
   {
   	cout << "Error: " << e_error.what() << endl;
   }

   if (result.rows() != 1)
   {
   	cout << "ere" << endl;
   	LocalBot->SendNotice(Source, "Failed to login as " + Parameters[0] + ".");
   }
   else
   {
   	// kind of nasty. Had to go throug mysql++'s code to figure this out.
   	if (Crypto::MatchPassword(Parameters[1], result.fetch_row()["password"].c_str() ))
   	{
   	   Source->SetAccount(Parameters[0]);
   	   LocalBot->RawMsg(LocalBot->theClient.GetNumeric().substr(0,2) + " AC " + Source->GetNumeric() + " " + Parameters[0]);
   	   LocalBot->SendNotice(Source, "You are now logged in as " + Parameters[0] + ".");
   	}
   	else
   	{
   	   LocalBot->SendNotice(Source, "Failed to login as " + Parameters[0] + ".");
   	}
   }
}

} // namespace cservice

} // namespace eNetworks
