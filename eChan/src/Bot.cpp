/*
 * eChan - Electronic Channel Services.
 * Copyright (C) 2003-2006 Alan Alvarez.
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
#include <map>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Bot.h"
#include "debug.h"
#include "OutBuffer.h"
#include "Server.h"
#include "tools.h"
#include "MsgTokenizer.h"
#include "Network.h"
#include "Client.h"
#include "Channel.h"
#include "ChannelClient.h"


using std::map;
using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{
Bot::Bot(const std::string& Numeric, const std::string& NickName, const std::string& Account, const std::string& UserName,
   	 const std::string& HostName, const std::string& B64IP, const std::string& Modes, const std::string& UserInfo) :
     theClient(Numeric, NickName, Account, UserName, HostName, B64IP, Modes, UserInfo, time(0), 1)
{
   if (!AddBot(Numeric, this))
   {
   	debug << "Error: Could not add bot " << NickName << endb;
   	exit(0);
   }

   string strMsg = LocalServer->GetNumeric();
   strMsg += " N ";
   strMsg += NickName;
   strMsg += " 1 ";
   strMsg += IntToString(time(0));
   strMsg += " ";
   strMsg += UserName;
   strMsg += " ";
   strMsg += HostName;
   strMsg += " +";
   strMsg += Modes;
   strMsg += " ";
   strMsg += B64IP;
   strMsg += " ";
   strMsg += Numeric;
   strMsg += " :";
   strMsg += UserInfo;

   RawMsg(strMsg);
}

void Bot::ChangeChannelMode(Channel* p_channel, const MsgTokenizer& p_nicknames, const char& p_mode, const bool& give)
{
   if (NULL == p_channel)
   	return;

   string l_msg = theClient.GetNumeric() + " M " + p_channel->GetName(); 

   // Give or take mode?
   if (give)
   	l_msg += " +";
   else
   	l_msg += " -";

   string l_modes("");
   string l_numerics("");
   for (unsigned int i = 0; i < p_nicknames.size(); i++)
   {
   	Client* l_Client = Network::Interface.FindClientByNickName(p_nicknames[i]);
   	ChannelClient* l_ChannelClient = p_channel->FindChannelClient(l_Client);
   	unsigned int l_count;
   	if (NULL != l_ChannelClient)
   	{
   	   l_ChannelClient->AddMode(p_mode);
   	   l_modes += p_mode;
   	   l_numerics += l_Client->GetNumeric();
   	   l_numerics += " ";
   	   l_count++;
   	}

   	if ((l_count == 6 || p_nicknames.size() - i < 6) && l_modes.length() > 0)
   	{
   	   // keep parsing nicks if we haven't gotten to the last one.
   	   if (p_nicknames.size()-1 != i)
   	   	continue;
 
   	   string l_send = l_msg;
           l_send += l_modes;
           l_send += " ";
           // erase last space.
           l_numerics.erase(l_numerics.length()-1,1);
           l_send += l_numerics;
           RawMsg(l_send);
   	   // restart count.
   	   l_count = 0;
   	}
   }
}


map<string, Bot*> Bot::BotMap = BotMapType();

} // namespace eNetworks
