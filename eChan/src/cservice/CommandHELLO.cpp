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

#include "CommandHELLO.h"
#include "SqlUser.h"
#include "SQL.h"
#include "Crypto.h"

using std::cout;
using std::endl;
using std::string;

namespace eNetworks
{

namespace cservice
{

CommandHELLO::CommandHELLO(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Command(theBot, theSource, refParameters)
{
   Syntax = "/msg " + LocalBot->theClient.GetNickName() + " hello <username> <password> <email>";
}

void CommandHELLO::Parser()
{
   if (Parameters.size() != 3)
   {
   	LocalBot->SendNotice(Source, "SYNTAX: " + Syntax);
   	return;
   }

   if (Source->HasAccount())
   {
   	LocalBot->SendNotice(Source, "You already have an account.");
   	return;
   }

   if (Parameters[2].find('@') == string::npos || Parameters[2].find('.') == string::npos)
   {
   	LocalBot->SendNotice(Source, "Bogus e-mail entry");
   	return;
   }

   SqlUser* l_SqlUser = SQL::Interface.FindUser(Parameters[0]);
   if (l_SqlUser != NULL)
   {
   	LocalBot->SendNotice(Source, "That username already exists");
   	return;
   }

   l_SqlUser = new SqlUser(0, Parameters[0], Crypto::EncryptPassword(Parameters[1]), Parameters[2]);
   l_SqlUser->update();

   LocalBot->SendNotice(Source, "Created username " + Parameters[0] + ".");
}

} // namespace cservice

} // namespace eNetworks
