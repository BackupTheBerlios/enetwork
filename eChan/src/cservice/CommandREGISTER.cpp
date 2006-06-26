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
#include "CommandREGISTER.h"
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

CommandREGISTER::CommandREGISTER(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Command(theBot, theSource, refParameters)
{
   Syntax = "/msg " + LocalBot->theClient.GetNickName() + " register <#channel> <username>";
}

void CommandREGISTER::Parser()
{
   if (Parameters.size() != 2)
   {
   	LocalBot->SendNotice(Source, "SYNTAX: " + Syntax);
   	return;
   }

   if (!IsChannel(Parameters[0]))
   {
   	LocalBot->SendNotice(Source, "Invalid channel");
   	return;
   }

   if (!SQL::Interface.HasEnoughAccess(Source, "*", Command::Level::REGISTER))
   {
        LocalBot->SendNotice(Source, "You don't have enough access to do that.");
        return;
   }


   if (NULL != SQL::Interface.FindChannel(Parameters[0]))
   {
   	LocalBot->SendNotice(Source, "Channel " + Parameters[0] + " is already registered.");
   	return;
   }

   SqlUser* l_SqlUser = SQL::Interface.FindUser(Parameters[1]);
   if (l_SqlUser == NULL)
   {
   	LocalBot->SendNotice(Source, "I don't know who " + Parameters[1] + " is.");
   	return;
   }

   // Create channel.
   SqlChannel* l_SqlChannel = new SqlChannel(0, Parameters[0], "NULL", "NULL");
   l_SqlChannel->update();

   // Create 500 access for this user.
   SqlChannelAccess* l_SqlChannelAccess = new SqlChannelAccess(0, l_SqlUser->getID(), l_SqlChannel->getID(), 500);
   l_SqlChannelAccess->update();

   LocalBot->SendNotice(Source, "Registered channel " + Parameters[0] + " to " + Parameters[1] + ".");

   // Join the channel.
   LocalBot->Join(Parameters[0]);
   // Op the bot.
   LocalBot->RawMsg(LocalBot->theClient.GetNumeric().substr(0,2) + " M " + Parameters[0] + " +o " + LocalBot->theClient.GetNumeric());
}

} // namespace cservice

} // namespace eNetworks
