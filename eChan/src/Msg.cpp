/*
 * eChan - Electronic Channel Services.
 * Copyright (C) 2003 Alan Alvarez.
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
#include <string>
#include <cstdlib>
#include <ctime>

#include "debug.h"
#include "MsgTokenizer.h"
#include "Msg.h"
#include "Msg_S.h"
#include "Msg_N.h"
#include "Msg_B.h"
#include "PreServerMsg.h"
#include "Server.h"
#include "P10Tokens.h"
#include "Network.h"

using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

Msg::Msg(const string &aCommand, const std::string &aToken) : Token(aToken), Parameters("")
{
cout << "[IN]: " << aCommand << endl;

   if (Token == Tokens::PRESERVER)
   {
   	ClientSrc = NULL; // no client source.
   	ServerSrc = NULL; // no server source
   	Parameters = aCommand.substr(7);
   }
   else if (Token == Tokens::PASS)
   {
   	Parameters = aCommand;
   } 
   else if (Token == Tokens::ERROR)
   {
   	debug << aCommand;
   	exit(0);
   }
   else
   {    
/*
   	if (aCommand.length() > aCommand.find(Token)+1+Token.length())
   	{
   	   Parameters = aCommand.substr(aCommand.find(Token)+Token.length());
//   	   cout << "Parameters[0]: " << Parameters[0] << endl;
   	}
*/

   	if (aCommand.find(' ') == 2) // This message came from a server.
   	{
   	   ServerSrc = eNetwork->FindServerByNumeric(aCommand.substr(0,2));
    	   ClientSrc = NULL;
   	   Parameters = aCommand.substr(3+Token.length()+1);
   	   if (ServerSrc == NULL)
   	   {
   	   	debug << "Can't find Server " << aCommand.substr(0,2) << " in my database";
   	   	exit(0);
   	   }
   	}
   	else if (aCommand.find(' ') == 5)
   	{
   	   ClientSrc = eNetwork->FindClientByNumeric(aCommand.substr(0,5)); 
   	   ServerSrc = NULL;
   	   Parameters = aCommand.substr(6+Token.length()+1);
   	   if (ClientSrc == NULL)
   	   {
   	   	debug << "Can't find client " << aCommand.substr(0,5) << " in my database"; 
   	   	exit(0);
   	   }
   	}
   	else
   	{
   	   debug << "Protocol Violation";
   	   exit(0);
   	}
   }
}

void Msg::Parser()
{
/*
   for (int i = 0; i < Parameters.size(); i++)
   {
   	cout << Parameters[i];
   }
  
   cout << endl;
*/
}

Msg *Msg::MsgParser(const std::string &command)
{
   string Token;

   // Get the token.
   if (command.find(" ") == 2 || command.find(" ") == 5)
   {
        if (command.length() >= 7 && command.substr(0,7) == "ERROR :")
        {
           return new Msg(command, Tokens::ERROR);
        }

        Token = command.substr(command.find(" ")+1);
        Token = Token.substr(0, Token.find(" "));
   }
   else
   {
        if (command.length() > 6 && command.substr(0,6) == "SERVER")
         return new PreServerMsg(command, Tokens::PRESERVER);
        else if (command.length() > 6 && command.substr(0,6) == "PASS :")
         return new Msg(command, Tokens::PASS);
        else
         return new Msg(command, "");
   }

   if (Token == Tokens::SERVER)
    return new Msg_S(command, Tokens::SERVER);
   else if (Token == Tokens::NICK)
    return new Msg_N(command, Tokens::NICK);
   else if (Token == Tokens::B)
    return new Msg_B(command, Tokens::B);
   else
    return new Msg(command, Token);

return NULL; // We're not supposed to get here, but just in case.
}


} // namespace eNetworks
