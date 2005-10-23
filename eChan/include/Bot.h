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

#ifndef ELECTRONIC_NETWORKS__BOT_H
#define ELECTRONIC_NETWORKS__BOT_H

#include <map>
#include <cstdlib>

#include "MsgSource.h"
#include "Client.h"
#include "MsgTokenizer.h"
#include "OutBuffer.h"

namespace eNetworks
{
class Bot
{
  public:
	// Takes care of setting the members no matter what kind of Msg it is.
	Bot(const std::string& Numeric, const std::string& NickName, const std::string& Account, const std::string& UserName,
   	    const std::string& HostName, const std::string& B64IP, const std::string& Modes, const std::string& UserInfo);

	virtual ~Bot() {};

	virtual void onPRIVMSG(const MsgSource& Source, const MsgTokenizer& Parameters) = 0;
   	virtual void onNOTICE(const MsgSource& Source, const MsgTokenizer& Parameters) = 0;
   	virtual void onKICK(const MsgSource& Source, const MsgTokenizer& Parameters) = 0;

   	virtual void onMsgMonitor(const MsgSource& Source, const MsgTokenizer& Parameters) = 0;

   	virtual void SendNotice(Client* Target, const std::string& Msg)
   	{
   	   OutBuffer::obInstance.insert(theClient.GetNumeric() + " O " + Target->GetNumeric() + " :" + Msg);
   	}

   	virtual void SendMsg(Client* Target, const std::string& Msg)
   	{
   	   OutBuffer::obInstance.insert(theClient.GetNumeric() + " P " + Target->GetNumeric() + " :" + Msg);
   	}

   	static Bot* FindBot(const std::string& Numeric)
   	{
   	   BotMapType::iterator iterBot = BotMap.find(Numeric);

   	   if (iterBot == BotMap.end())
   	   	return NULL;

   	   return iterBot->second;
   	}

   	Client theClient;

   private:
   	static bool AddBot(const std::string &Numeric, Bot* theBot)
   	{
   	   return BotMap.insert(BotMapType::value_type(Numeric, theBot)).second;
   	}

   	typedef std::map<std::string, Bot*> BotMapType;
   	static BotMapType BotMap;
};


} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__BOT_H
