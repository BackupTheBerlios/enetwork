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

map<string, Bot*> Bot::BotMap = BotMapType();

} // namespace eNetworks
