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

#ifndef ELECTRONIC_NETWORKS__CSERVICE_COMMAND_H
#define ELECTRONIC_NETWORKS__CSERVICE_COMMAND_H

#include <string>

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
   	enum CommandNames
   	{
   	   NONE = 0,
   	   WHOIS,
   	   QUOTE
   	};

   	virtual void Parser() = 0;

   	static bool AddCommand(const std::string& CommandName, const CommandNames& theCommand)
   	{
   	   return CommandMap.insert(CommandMapType::value_type(CommandName, theCommand)).second;
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
   	static CommandNames GetCommand(const std::string& CommandName)
   	{
   	   CommandMapType::iterator iterCommand = CommandMap.find(CommandName);

   	   if (CommandMap.end() == iterCommand)
   	   	return NONE;

   	   return iterCommand->second;
   	}

   	typedef std::map<std::string, CommandNames, noCaseCompare> CommandMapType;
   	static CommandMapType CommandMap;
};

} // namespace eNetworks

} // namespace cservice

#endif // ELECTRONIC_NETWORKS__CSERVICE_COMMAND_H