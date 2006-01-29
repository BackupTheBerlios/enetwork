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
#include <mysql++.h>

#include "BotCService.h"
#include "Network.h"
#include "MsgMonitor.h"
#include "P10Tokens.h"
#include "Server.h"
#include "Channel.h"
#include "Command.h"
#include "CommandWHOIS.h"
#include "SqlManager.h"

using std::cout;
using std::endl;
using mysqlpp::Query;
using mysqlpp::Result;

namespace eNetworks
{
BotCService::BotCService(ConfigParser& theConfigParser) : 
   	     Bot(theConfigParser.GetConfiguration("NUMERIC")+"AAA", theConfigParser.GetConfiguration("NICK"), "", 
                 theConfigParser.GetConfiguration("USERNAME"), theConfigParser.GetConfiguration("HOSTNAME"), 
    	   	 "DAqAoB", "idk", theConfigParser.GetConfiguration("CLIENTINFO"))
{
   MsgMonitor::AddMonitor(Tokens::END_OF_BURST, this);
   cservice::Command::AddCommand("whois", cservice::Command::WHOIS, cservice::Command::Level::WHOIS);
   cservice::Command::AddCommand("quote", cservice::Command::QUOTE, cservice::Command::Level::QUOTE);
   cservice::Command::AddCommand("login", cservice::Command::LOGIN, cservice::Command::Level::LOGIN);
}

void BotCService::onPRIVMSG(const MsgSource& Source, const MsgTokenizer& Parameters)
{
   cout << "[IN]: " << Source.GetName() << " PRIVMSG " << theClient.GetNickName() << " :";
   for (unsigned int i = 0; i < Parameters.size(); i++)
   	cout << Parameters[i] << " ";

   cout << endl;

   std::string Message = "";

   for (unsigned int i = 0; i < Parameters.size(); i++)
   {
   	Message += Parameters[i];
   	Message += " ";
   }

   // Reply to CTCP messages.
   if (Parameters[Parameters.size()-1] == "\001VERSION\001")
   {
   	SendNotice(Network::Interface.FindClientByNumeric(Source.GetNumeric()), "\001VERSION eChan v0.5.2 Alpha by Alan Alvarez (clsk@IRC).\001");
   	return;
   }

   Message = Message.erase(Message.length()-1, 1); // get rid of extra space character.
   cservice::Command::ParseCommands(this, Network::Interface.FindClientByNumeric(Source.GetNumeric()), Message);
}

void BotCService::onNOTICE(const MsgSource& Source, const MsgTokenizer& Parameters)
{
   cout << "[IN]: " << Source.GetName() << " NOTICE " << theClient.GetNickName() << " :";
   for (unsigned int i = 0; i < Parameters.size(); i++)
   	cout << Parameters[i] << " " << endl;

   cout << endl;
}

// We shouldn't be getting kicked in the first place.
void BotCService::onKICK(const MsgSource& Source, const MsgTokenizer& Parameters)
{
}

void BotCService::onMsgMonitor(const Tokens::Token& _Token, const MsgSource& Source, const MsgTokenizer& Parameters)
{
   // we only monitor END_OF_BURST message so don't worry about parsing other messages.
   // Lets JOIN to all registered channels.
   Query query = SqlManager::query();
   query << "SELECT SqlChannel.name FROM SqlChannel";

   Result result = query.store();

   Channel* theChannel = NULL;
   for (Result::iterator Iter = result.begin(); Iter != result.end(); Iter++)
   {
   	string strChannel = (*Iter).at(0).c_str();
   	if (strChannel[0] != '#') // Check for special channels.
   	   continue;

   	theChannel = Network::Interface.FindChannel(strChannel);
   	if (NULL == theChannel) // if channel doesn't exist, create it.
   	{
   	   RawMsg(theClient.GetNumeric() + " C " + strChannel + " " + IntToString(time(0)));
   	   Network::Interface.AddChannel(strChannel, time(0));

   	   Network::Interface.FindChannel(strChannel)->AddChannelClient(&theClient);
   	}
   	else
   	{
   	   RawMsg(theClient.GetNumeric() + " J " + strChannel + " " + IntToString(theChannel->GetTimeStamp()));
   	   theChannel->AddChannelClient(&theClient);
   	}
   	// OP the bot.
   	RawMsg(theClient.GetNumeric().substr(0,2) + " M " + strChannel + " +o " + theClient.GetNumeric());
   }
}

} // namespace eNetworks
