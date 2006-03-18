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

#include "MsgTokenizer.h"
#include "CommandWHOIS.h"
#include "Network.h"
#include "Client.h"
#include "Server.h"
#include "SQL.h"

using std::cout;
using std::endl;

namespace eNetworks
{

namespace cservice
{

CommandWHOIS::CommandWHOIS(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Command(theBot, theSource, refParameters)
{
   Syntax = "/msg " + LocalBot->theClient.GetNickName() + " whois <nick>";
}

void CommandWHOIS::Parser()
{
   if (Parameters.size() != 1)
   {
   	LocalBot->SendNotice(Source, "SYNTAX: " + Syntax);
   	return;
   }

   if (!SQL::Interface.HasEnoughAccess(Source, "*", Command::Level::WHOIS))
   {
   	LocalBot->SendNotice(Source, "You don't have enough access to perform this command.");
   	return;
   }

   ClientTarget = Network::Interface.FindClientByNickName(Parameters[0]);

   if (NULL == ClientTarget)
   {
// Got to love windows support :).
#ifdef WIN32
   	if (_strcmpi(Parameters[0].c_str(), LocalBot->theClient.GetNickName().c_str() ) == 0)
#else
   	if (strcasecmp(Parameters[0].c_str(), LocalBot->theClient.GetNickName().c_str() ) == 0)
#endif
           LocalBot->SendNotice(Source, "I am the revolution.");
        else
           LocalBot->SendNotice(Source, "Can't find user " + Parameters[0] + ".");

        return;
   }

   string Message = ClientTarget->GetNickName() + " " + ClientTarget->GetUserName() + "@" + ClientTarget->GetHostName() + 
   	   	    " * " + ClientTarget->GetUserInfo() + " (" + ClientTarget->GetNumeric() + ")";
   LocalBot->SendNotice(Source, Message);

   Message = ClientTarget->GetNickName() + " on";

   for(Client::ChannelMapType::iterator iter = ClientTarget->ChannelMap.begin(); iter != ClientTarget->ChannelMap.end(); iter++)
   {
   	Message += " ";
   	Message += iter->first;
   }

   LocalBot->SendNotice(Source, Message);

   Server* ptrServer = Network::Interface.FindServerByNumeric(ClientTarget->GetNumeric().substr(0, 2));   

   Message = ClientTarget->GetNickName() + " using " + ptrServer->GetName() + " " + ptrServer->GetDescription();

   LocalBot->SendNotice(Source, Message);

   Message = ClientTarget->GetNickName() + " has modes (" + ClientTarget->Modes + ")";

   LocalBot->SendNotice(Source, Message);
}

} // namespace cservice

} // namespace eNetworks
