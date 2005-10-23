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

#include "BotCService.h"
#include "Network.h"
#include "MsgMonitor.h"
#include "P10Tokens.h"
#include "Server.h"
#include "Channel.h"
#include "Command.h"
#include "CommandWHOIS.h"

using std::cout;
using std::endl;

namespace eNetworks
{
BotCService::BotCService(ConfigParser& theConfigParser) : 
   	     Bot(theConfigParser.GetConfiguration("NUMERIC")+"AAA", theConfigParser.GetConfiguration("NICK"), "", 
                 theConfigParser.GetConfiguration("USERNAME"), theConfigParser.GetConfiguration("HOSTNAME"), 
    	   	 "DAqAoB", "idk", theConfigParser.GetConfiguration("CLIENTINFO"))
{
   MsgMonitor::AddMonitor(Tokens::END_OF_BURST, this);   
   cservice::Command::AddCommand("whois", cservice::Command::WHOIS);
   cservice::Command::AddCommand("quote", cservice::Command::QUOTE);
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

void BotCService::onKICK(const MsgSource& Source, const MsgTokenizer& Parameters)
{
}

void BotCService::onMsgMonitor(const MsgSource& Source, const MsgTokenizer& Parameters)
{
   Channel *theChannel = Network::Interface.FindChannel("#CService");
   if (NULL == theChannel)
   {
   	OutBuffer::obInstance.insert(theClient.GetNumeric() + " C #CService " + IntToString(time(0)));
   	Network::Interface.AddChannel("#CService", time(0));

   	Network::Interface.FindChannel("#CService")->AddChannelClient(&theClient);
   }
   else
   {
   	OutBuffer::obInstance.insert(theClient.GetNumeric() + " J #CService " + IntToString(theChannel->GetTimeStamp()));
  	 theChannel->AddChannelClient(&theClient);
   }
}

}
