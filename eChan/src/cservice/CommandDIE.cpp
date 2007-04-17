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

#include "CommandDIE.h"
#include "Server.h"
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

CommandDIE::CommandDIE(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Command(theBot, theSource, refParameters)
{
   Syntax = "/msg " + LocalBot->theClient.GetNickName() + " die [reason]";
}

void CommandDIE::Parser()
{
   if (!SQL::Interface.HasEnoughAccess(Source, "*", Command::Level::DIE))
   {
   	LocalBot->SendNotice(Source, "You don't have enough access to do that.");
   	return;   	
   }

   string l_reason = "";
   if (Parameters.size() > 0)
   {
   	l_reason = Parameters.assamble(0);
   }

   l_reason += " (By request of " + Source->GetNickName() + ")";   

   LocalBot->RawMsg(LocalBot->theClient.GetNumeric() + " Q :" + l_reason);
   LocalBot->RawMsg(LocalServer->GetNumeric() + " SQ " + LocalServer->GetName() + " 0");
}

} // namespace cservice

} // namespace eNetworks
