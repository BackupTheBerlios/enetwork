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

#include <map>
#include <string>
#include <iostream>

#include "Command.h"
#include "CommandWHOIS.h"
#include "CommandQUOTE.h"
#include "CommandHELLO.h"
#include "CommandLOGIN.h"
#include "CommandUP.h"
#include "CommandDOWN.h"
#include "CommandOP.h"
#include "CommandDEOP.h"
#include "CommandVOICE.h"
#include "CommandDEVOICE.h"
#include "CommandREGISTER.h"
#include "tools.h"

using std::map;
using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

namespace cservice
{

void Command::ParseCommands(Bot* theBot, Client* theSource, const std::string& strCommand)
{
   string theCommand = strCommand.substr(0, strCommand.find(" "));
   string strParameters("");

   if (strCommand.find(" ") != string::npos)
   	strParameters = strCommand.substr(strCommand.find(" ")+1);

   MsgTokenizer mtTemp(strParameters, NULL);

   Command* cmd = NULL;
   switch (GetCommand(theCommand))
   {
   	case LOGIN:
   	   cmd = new CommandLOGIN(theBot, theSource, mtTemp);
   	   break;

   	case OP:
   	   cmd = new CommandOP(theBot, theSource, mtTemp);
   	   break;

   	case DEOP:
   	   cmd = new CommandDEOP(theBot, theSource, mtTemp);
   	   break;

   	case VOICE:
   	   cmd = new CommandVOICE(theBot, theSource, mtTemp);
   	   break;

   	case DEVOICE:
   	   cmd = new CommandDEVOICE(theBot, theSource, mtTemp);
   	   break;

   	case UP:
   	   cmd = new CommandUP(theBot, theSource, mtTemp);
   	   break;

   	case DOWN:
   	   cmd = new CommandDOWN(theBot, theSource, mtTemp);
   	   break;

   	case HELLO:
   	   cmd = new CommandHELLO(theBot, theSource, mtTemp);
   	   break;

   	case REGISTER:
   	   cmd = new CommandREGISTER(theBot, theSource, mtTemp);
   	   break;
 
   	case WHOIS:
   	   cmd = new CommandWHOIS(theBot, theSource, mtTemp);
   	   break;

   	case QUOTE:
   	   cmd = new CommandQUOTE(theBot, theSource, mtTemp);
   	   break;

   	case NONE:
   	   break;
   }

   if (NULL != cmd)
   {
   	cmd->Parser();
   	delete cmd;
   	cmd = NULL;
   }
}

const unsigned int Command::Level::LOGIN = 0;
const unsigned int Command::Level::WHOIS = 600;
const unsigned int Command::Level::QUOTE = 1000;
const unsigned int Command::Level::UP = 100;
const unsigned int Command::Level::DOWN = 100;
const unsigned int Command::Level::VOICE = 25;
const unsigned int Command::Level::DEVOICE = 25;
const unsigned int Command::Level::HELLO = 0;
const unsigned int Command::Level::REGISTER = 700;

map<string, Command::CommandName, noCaseCompare> Command::CommandMap = CommandMapType();
} // namespace cservice

} // namespace eNetworks
