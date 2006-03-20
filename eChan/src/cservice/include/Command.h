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

#ifndef ELECTRONIC_NETWORKS__CSERVICE_COMMAND_H
#define ELECTRONIC_NETWORKS__CSERVICE_COMMAND_H

#include <string>
#include <utility>

#include "Client.h"
#include "Channel.h"
#include "MsgTokenizer.h"
#include "tools.h"
#include "Bot.h"

namespace eNetworks
{

namespace cservice
{

class Command
{
   public:
   	Command(Bot* theBot, Client* theSource, const MsgTokenizer& refParameters) : Source(theSource), Parameters(refParameters), LocalBot(theBot)
   	{}

   	virtual ~Command() {}
   	enum CommandName
   	{
   	   NONE = 0,
   	   WHOIS,
   	   QUOTE,
   	   LOGIN,
   	   UP,
   	   DOWN,
   	   OP,
   	   DEOP,
   	   VOICE,
   	   DEVOICE,
           HELLO,
           REGISTER,
           ADDUSER
   	};


   	struct Level
   	{
   	   static const unsigned int LOGIN;
   	   static const unsigned int WHOIS;
   	   static const unsigned int QUOTE;
   	   static const unsigned int UP;
   	   static const unsigned int DOWN;
   	   static const unsigned int OP;
   	   static const unsigned int DEOP;
   	   static const unsigned int VOICE;
   	   static const unsigned int DEVOICE;
   	   static const unsigned int HELLO;
   	   static const unsigned int REGISTER;
   	   static const unsigned int ADDUSER;
   	};

   	virtual void Parser() = 0;

   	static void AddCommand(const std::string& CommandName, const CommandName& theCommand)
   	{
   	   CommandMap.insert(CommandMapType::value_type(CommandName, theCommand));
   	}

   	static void ParseCommands(Bot* theBot, Client* theSource, const std::string& strCommand);

   protected:
   	Client* Source;
   	Client* ClientTarget;   
   	Channel* ChannelTarget;
   	MsgTokenizer Parameters;
   	std::string Syntax;
   	Bot* LocalBot;

   private:
   	static CommandName GetCommand(const std::string& p_CommandName)
   	{
   	   CommandMapType::iterator iterCommand = CommandMap.find(p_CommandName);

   	   if (CommandMap.end() == iterCommand)
   	   	return NONE;

   	   return iterCommand->second;
   	}

   	typedef std::map<std::string, CommandName, noCaseCompare> CommandMapType;
   	static CommandMapType CommandMap;
};

} // namespace eNetworks

} // namespace cservice

#endif // ELECTRONIC_NETWORKS__CSERVICE_COMMAND_H
