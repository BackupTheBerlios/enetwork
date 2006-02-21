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

#include "CommandDOWN.h"
#include "Network.h"
#include "Channel.h"
#include "SqlChannel.h"
#include "SQL.h"

using std::cout;
using std::endl;

namespace eNetworks
{

namespace cservice
{

CommandDOWN::CommandDOWN(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Command(theBot, theSource, refParameters)
{
   Syntax = "/msg " + LocalBot->theClient.GetNickName() + " down <#channel>";
}

void CommandDOWN::Parser()
{
   // Is this channel registered?
   SqlChannel* l_SqlChannel = SQL::Interface.FindChannel(Parameters[0]);
   if (NULL == l_SqlChannel)
   {
   	LocalBot->SendNotice(Source, "Channel " + Parameters[0] + " doesn't appear to be registered.");
   	return;
   }

   // Does the channel exist?
   Channel* l_Channel = Network::Interface.FindChannel(Parameters[0]);
   if (NULL == l_Channel)
   {
   	LocalBot->SendNotice(Source, "Can't find channel " + Parameters[0] + " in Network database");
   	return;
   }

   // Are we in that channel?
   if (!l_Channel->IsChannelClient(&LocalBot->theClient))
   {
   	LocalBot->SendNotice(Source, "I'm not in " + Parameters[0]);
   	return;
   }

   if (!SQL::Interface.HasEnoughAccess(Source, l_Channel, Command::Level::DOWN))
   {
   	LocalBot->SendNotice(Source, "You don't have enough access to perform this command");
   	return;
   }   

   LocalBot->TakeOP(l_Channel, Source->GetNickName());   
}

} // namespace cservice

} // namespace eNetworks
