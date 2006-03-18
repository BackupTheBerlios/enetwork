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

#ifndef ELECTRONIC_NETWORKS__BOT_H
#define ELECTRONIC_NETWORKS__BOT_H

#include <map>
#include <cstdlib>

#include "P10Tokens.h"
#include "MsgSource.h"
#include "MsgTokenizer.h"
#include "OutBuffer.h"
#include "Network.h"
#include "Client.h"
#include "Channel.h"
#include "ChannelClient.h"

namespace eNetworks
{
// This class represents a bot that's connected to the local server.
// Derive from this class if you would like to create a new bot.
class Bot
{
  public:
	// Constructor will introduce the bot to the network.
	Bot(const std::string& Numeric, const std::string& NickName, const std::string& Account, const std::string& UserName,
   	    const std::string& HostName, const std::string& B64IP, const std::string& Modes, const std::string& UserInfo);

   	// TODO: SEND Quit message and get rid of this bot.
	virtual ~Bot() {};

   	// override this function to respond to Private messages sent to this bot.
	virtual void onPRIVMSG(const MsgSource& Source, const MsgTokenizer& Parameters) = 0;
   	
   	// override this function to respond to notices sent to this bot.
   	virtual void onNOTICE(const MsgSource& Source, const MsgTokenizer& Parameters) = 0;

   	// override this function to respond when this bot is kicked.
   	virtual void onKICK(const MsgSource& Source, const MsgTokenizer& Parameters) = 0;

   	// override this function to respond to server messages you registered to be monitored by this bot.
   	virtual void onMsgMonitor(const Tokens::Token& _Token, const MsgSource& Source, const MsgTokenizer& Parameters) = 0;

   	// sends a notice (Token O) to another user.
   	virtual void SendNotice(Client* Target, const std::string& Msg)
   	{
   	   OutBuffer::obInstance.insert(theClient.GetNumeric() + " O " + Target->GetNumeric() + " :" + Msg);
   	}

   	// sends a private message (Token P) to another user.
   	virtual void SendMsg(Client* Target, const std::string& Msg)
   	{
   	   OutBuffer::obInstance.insert(theClient.GetNumeric() + " P " + Target->GetNumeric() + " :" + Msg);
   	}

   	// sends a raw message to the uplink.
   	virtual void RawMsg(const std::string& Msg)
   	{
   	   OutBuffer::obInstance.insert(Msg);
   	}

   	virtual void GiveOP(Channel* p_channel, const MsgTokenizer& p_nicknames)
   	{
   	   GiveChannelMode(p_channel, p_nicknames, 'o');
   	}

   	virtual void GiveOP(const std::string& channel, const MsgTokenizer& p_nicknames)
   	{
   	   GiveOP(Network::Interface.FindChannel(channel), p_nicknames);
   	}

   	virtual void TakeOP(Channel* p_channel, const MsgTokenizer& p_nicknames)
   	{
   	   TakeChannelMode(p_channel, p_nicknames, 'o');
   	}

   	virtual void TakeOP(const std::string& channel, const MsgTokenizer& p_nicknames)
   	{
   	   TakeOP(Network::Interface.FindChannel(channel), p_nicknames);
   	}

   	virtual void GiveVoice(Channel* p_channel, const MsgTokenizer& p_nicknames)
   	{
   	   GiveChannelMode(p_channel, p_nicknames, 'v');
   	}

   	virtual void GiveVoice(const std::string& channel, const MsgTokenizer& p_nicknames)
   	{
   	   GiveVoice(Network::Interface.FindChannel(channel), p_nicknames);
   	}

   	virtual void TakeVoice(Channel* p_channel, const MsgTokenizer& p_nicknames)   	
   	{
   	   TakeChannelMode(p_channel, p_nicknames, 'v');
   	}

   	virtual void TakeVoice(const std::string& channel, const MsgTokenizer& p_nicknames)
   	{
   	   TakeVoice(Network::Interface.FindChannel(channel), p_nicknames);
   	}

   	virtual void Join(const std::string& channel);
   	virtual void Join(Channel* channel);

   	// find a registered bot.
   	static Bot* FindBot(const std::string& Numeric)
   	{
   	   BotMapType::iterator iterBot = BotMap.find(Numeric);

   	   if (iterBot == BotMap.end())
   	   	return NULL;

   	   return iterBot->second;
   	}

   	// instance of the Client object that represents this bot on the network.
   	Client theClient;

   private:
   	// add a bot to list of bots in the local server.
   	// This function is to be called by the Bot constructor only.
   	static bool AddBot(const std::string &Numeric, Bot* theBot)
   	{
   	   return BotMap.insert(BotMapType::value_type(Numeric, theBot)).second;
   	}

   	// List of bots associated by numeric.
   	typedef std::map<std::string, Bot*> BotMapType;
   	static BotMapType BotMap;
   	void ChangeChannelMode(Channel* p_channel, const MsgTokenizer& p_nicknames, const char& p_mode, const bool& give);
   	void GiveChannelMode(Channel* p_channel, const MsgTokenizer& p_nicknames, const char& p_mode)
   	{
   	   ChangeChannelMode(p_channel, p_nicknames, p_mode, true);
   	}

   	void TakeChannelMode(Channel* p_channel, const MsgTokenizer& p_nicknames, const char& p_mode)
   	{
   	   ChangeChannelMode(p_channel, p_nicknames, p_mode, false);
   	}
};


} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__BOT_H
