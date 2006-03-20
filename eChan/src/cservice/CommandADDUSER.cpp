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

#include "Command.h"
#include "CommandADDUSER.h"
#include "SqlUser.h"
#include "SqlChannel.h"
#include "SqlChannelAccess.h"
#include "SQL.h"
#include "tools.h"

using std::cout;
using std::endl;
using std::string;

namespace eNetworks
{

namespace cservice
{

CommandADDUSER::CommandADDUSER(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Command(theBot, theSource, refParameters)
{
   Syntax = "/msg " + LocalBot->theClient.GetNickName() + " adduser <#channel> <username> <level>";
}

void CommandADDUSER::Parser()
{
   if (Parameters.size() != 3)
   {
   	LocalBot->SendNotice(Source, "SYNTAX: " + Syntax);
   	return;
   }

   if (Parameters[0][0] != '#')
   {
   	LocalBot->SendNotice(Source, "Invalid channel");
   	return;
   }

   if (!IsDigit(Parameters[2]))
   {
   	LocalBot->SendNotice(Source, "Bogus access level.");
   	return;
   }

   unsigned int l_level = StringToInt(Parameters[2]);

   if (l_level > 500 || l_level == 0)
   {
   	LocalBot->SendNotice(Source, "Bogus access level number.");
   	return;
   }

   if (!SQL::Interface.HasEnoughAccess(Source, Parameters[0], Command::Level::ADDUSER) &&
       !SQL::Interface.HasEnoughAccess(Source, "*", Command::Level::ADDUSER))
   {
           LocalBot->SendNotice(Source, "You don't have enough access to do that.");
           return;
   }

   SqlChannel* l_SqlChannel = SQL::Interface.FindChannel(Parameters[0]);
   if (NULL == l_SqlChannel)
   {
   	LocalBot->SendNotice(Source, "Channel " + Parameters[0] + " is not registered.");
   	return;
   }

   SqlUser* l_SqlUser = SQL::Interface.FindUser(Parameters[1]);
   if (l_SqlUser == NULL)
   {
   	LocalBot->SendNotice(Source, "I don't know who " + Parameters[1] + " is.");
   	return;
   }

   if (SQL::Interface.GetAccessLevel(Source, l_SqlChannel->getID()) <= l_level)
   {
   	LocalBot->SendNotice(Source, "Cannot add a user with equal or higher access than your own.");
   	return;
   }

   // Create 500 access for this user.
   SqlChannelAccess* l_SqlChannelAccess = new SqlChannelAccess(0, l_SqlUser->getID(), l_SqlChannel->getID(), l_level);
   l_SqlChannelAccess->update();

   LocalBot->SendNotice(Source, "Added user " + l_SqlUser->getUsername() + " to channel " + l_SqlChannel->getName() + " with access level " + Parameters[2] + ".");
}

} // namespace cservice

} // namespace eNetworks
