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

#include "CommandREMUSER.h"
#include "tools.h"
#include "SQL.h"
#include "SqlUser.h"
#include "SqlChannel.h"
#include "SqlChannelAccess.h"

using std::cout;
using std::endl;
using std::string;

namespace eNetworks
{

namespace cservice
{

CommandREMUSER::CommandREMUSER(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Command(theBot, theSource, refParameters)
{
   Syntax = "/msg " + LocalBot->theClient.GetNickName() + " remuser <#channel> <username>";
}

void CommandREMUSER::Parser()
{
   if (Parameters.size() != 2)
   {
   	LocalBot->SendNotice(Source, "SYNTAX: " + Syntax);
   	return;
   }

   if (Parameters[0] != "*" && !IsChannel(Parameters[0]))
   {
   	LocalBot->SendNotice(Source, "Invalid channel");
   	return;
   }

   SqlChannel* l_SqlChannel = SQL::Interface.FindChannel(Parameters[0]);
   if (NULL == l_SqlChannel)
   {
        LocalBot->SendNotice(Source, "Channel " + Parameters[0] + " is not registered.");
        return;
   }

   if (!SQL::Interface.HasEnoughAccess(Source, Parameters[0], Command::Level::REMUSER) &&
       !SQL::Interface.HasEnoughAccess(Source, "*", Command::Level::REMUSER))
   {
           LocalBot->SendNotice(Source, "You don't have enough access to do that.");
           return;
   }

   SqlUser* l_SqlUser = SQL::Interface.FindUser(Parameters[1]);
   if (l_SqlUser == NULL)
   {
        LocalBot->SendNotice(Source, "I don't know who " + Parameters[2] + " is.");
        return;
   }
  
   SqlChannelAccess* l_SqlChannelAccess = SQL::Interface.FindChannelAccess(l_SqlUser->getID(), l_SqlChannel->getID());
   if (l_SqlChannelAccess == NULL)
   {
   	LocalBot->SendNotice(Source, "User " + Parameters[1] + " does not have access in " + Parameters[0] + ".");
   	return;
   }

   if (SQL::Interface.GetAccessLevel(Source, l_SqlChannel->getID()) <= l_SqlChannelAccess->getLevel())
   {
        LocalBot->SendNotice(Source, "Cannot remove user that has equal or higher access than you.");
        return;
   }

   l_SqlChannelAccess->Delete();

   LocalBot->SendNotice(Source, "Removed " + Parameters[1] + " from " + Parameters[0] + ".");
}

} // namespace cservice

} // namespace eNetworks
