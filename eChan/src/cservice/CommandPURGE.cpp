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

#include "CommandPURGE.h"
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

CommandPURGE::CommandPURGE(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Command(theBot, theSource, refParameters)
{
   Syntax = "/msg " + LocalBot->theClient.GetNickName() + " purge <#channel>";
}

void CommandPURGE::Parser()
{
   if (Parameters.size() < 1)
   {
   	LocalBot->SendNotice(Source, "SYNTAX: " + Syntax);
   	return;
   }

   if (!IsChannel(Parameters[0]))
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

   if (!SQL::Interface.HasEnoughAccess(Source, "*", Command::Level::PURGE))
   {
           LocalBot->SendNotice(Source, "You don't have enough access to do that.");
           return;
   }

   l_SqlChannel->Delete();

   LocalBot->SendNotice(Source, "Removed channel " + Parameters[0] + " from database.");
}

} // namespace cservice

} // namespace eNetworks
