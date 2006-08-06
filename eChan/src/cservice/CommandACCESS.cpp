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

#include "CommandACCESS.h"
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

CommandACCESS::CommandACCESS(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Command(theBot, theSource, refParameters)
{
   Syntax = "/msg " + LocalBot->theClient.GetNickName() + " access <#channel> <username>";
}

void CommandACCESS::Parser()
{
   if (Parameters.size() != 2)
   {
   	LocalBot->SendNotice(Source, "SYNTAX: " + Syntax);
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

   SqlChannelAccess* l_SqlChannelAccess = SQL::Interface.FindChannelAccess(l_SqlUser->getID(), l_SqlChannel->getID());
   if (l_SqlChannelAccess == NULL)
   {
   	LocalBot->SendNotice(Source, "No Match!");
   	return;
   }
   else
   {
   	string l_auto_mode;
   	switch (l_SqlChannelAccess->getAutomode())
   	{
   	   case SqlChannelAccess::AUTOMODE_NONE:
   	   	l_auto_mode = "NONE";
   	   	break;
   	   case SqlChannelAccess::AUTOMODE_OP:
   	   	l_auto_mode = "OP";
   	   	break;
   	   case SqlChannelAccess::AUTOMODE_VOICE:
   	   	l_auto_mode = "VOICE";
   	   	break;
   	}

   	LocalBot->SendNotice(Source, "USER: " + l_SqlUser->getUsername() + " ACCESS: " + IntToString(l_SqlChannelAccess->getLevel()));
   	LocalBot->SendNotice(Source, "CHANNEL: " + l_SqlChannel->getName() + " -- AUTOMODE: " + l_auto_mode);
   }
}

} // namespace cservice

} // namespace eNetworks
