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

#include <pthread.h>
#include <string>
#include <iostream>
#include <cstdlib>

#include "Msg.h"
#include "Msg_B.h"
#include "Msg_C.h"
#include "Msg_CM.h"
#include "Msg_EB.h"
#include "Msg_G.h"
#include "Msg_J.h"
#include "Msg_K.h"
#include "Msg_L.h"
#include "Msg_M.h"
#include "Msg_N.h"
#include "Msg_O.h"
#include "Msg_OM.h"
#include "Msg_P.h"
#include "Msg_Q.h"
#include "Msg_S.h"
#include "Msg_SQ.h"
#include "Msg_T.h"
#include "PreServerMsg.h"
#include "Thread.h"
#include "MsgParseSystem.h"
#include "InBuffer.h"
#include "MsgSource.h"
#include "MsgTokenizer.h"
#include "Client.h"
#include "Server.h"
#include "Network.h"
#include "debug.h"
#include "P10Tokens.h"

using std::cout;
using std::endl;

namespace eNetworks
{

void MsgParseSystem::Execute()
{
   do
   {
   	string command = InBuffer::ibInstance.pop();
   	string Token("");
   	MsgTokenizer Parameters("");
   	MsgSource Source;
   	Msg* eMsg = NULL;

   	cout << "[IN]: " << command << endl;

   	// Get the token & Source.
   	if (command.find(" ") == 2 || command.find(" ") == 5)
   	{
           if (command.length() >= 7 && command.substr(0,7) == "ERROR :")
           {
           	debug << command << endb;
   	   	exit(0);
           }

   	   Token = command.substr(command.find(" ")+1);
   	   Token = Token.substr(0, Token.find(" "));

   	   if (command.find(' ') == 2) // This message came from a server.
           {
           	Server* ServerSrc = Network::Interface.FindServerByNumeric(command.substr(0,2));
           	if (ServerSrc == NULL)
           	{
                   debug << "Can't find Server " << command.substr(0,2) << " in my database" << endb;
                   exit(0);
           	}
   	   	Source = ServerSrc;
   	   	Parameters = command.substr(3+Token.length()+1);

           }
           else if (command.find(' ') == 5) // This Message came from a client.
           {
           	Client* ClientSrc = Network::Interface.FindClientByNumeric(command.substr(0,5));
           	if (ClientSrc == NULL)
           	{
   	   	   debug << "Can't find client " << command.substr(0,5) << " in my database" << endb;
                   exit(0);
           	}
   	   	Source = ClientSrc;
   	   	Parameters = command.substr(6+Token.length()+1);
           }
   	}
   	else
   	{  // This is our UPLINK.
   	   if (command.length() > 6 && command.substr(0,6) == "SERVER")
   	   {
   	   	Parameters = command.substr(7);
   	   	eMsg = new PreServerMsg (Source, Parameters);
   	   	eMsg->Parser();
   	   	delete eMsg;
   	   	eMsg = NULL;
   	   	continue;
   	   }
   	   else if (command.length() > 6 && command.substr(0,6) == "PASS :")
   	   {
   	   	continue;
   	   }
   	   else
   	   {
   	   	debug << "Error: Protocol Violation in MsgParseSystem When Parsing the message." << endb;
   	   	exit(0);
   	   }
   	}

   	switch(eTokens->GetToken(Token))
   	{
   	   case Tokens::PRIVMSG:
   	   	eMsg = new Msg_P(Source, Parameters);
   	   	break;

   	   case Tokens::PING:
   	   	eMsg = new Msg_G(Source, Parameters);   	   	
   	   	break;

   	   case Tokens::CREATE:
   	   	eMsg = new Msg_C(Source, Parameters);
   	  	break;

   	   case Tokens::NICK:
   	   	eMsg = new Msg_N(Source, Parameters);
   	   	break;

   	   case Tokens::QUIT:
   	   	eMsg = new Msg_Q(Source, Parameters);
   	   	break;

   	   case Tokens::MODE:
   	   	eMsg = new Msg_M(Source, Parameters);
   	   	break;

   	   case Tokens::KICK:
   	   	eMsg = new Msg_K(Source, Parameters);
   	   	break;

   	   case Tokens::TOPIC:
   	   	eMsg = new Msg_T(Source, Parameters);
   	   	break;

   	   case Tokens::NOTICE:
   	   	eMsg = new Msg_O(Source, Parameters);
   	   	break;

   	   case Tokens::OPMODE:
   	   	eMsg = new Msg_OM(Source, Parameters);
   	   	break;

   	   case Tokens::CLEARMODE:
   	   	eMsg = new Msg_CM(Source, Parameters);
   	   	break;

   	   case Tokens::B:
   	   	eMsg = new Msg_B(Source, Parameters);
   	   	break;

   	   case Tokens::BURST:
   	   	eMsg = new Msg_Burst(Source, Parameters);
   	   	break;

   	   case Tokens::SERVER:
   	   	eMsg = new Msg_S(Source, Parameters);
   	   	break;

   	   case Tokens::END_OF_BURST:
   	   	eMsg = new Msg_EB(Source, Parameters);
   	   	break;

   	   case Tokens::JOIN:
   	   	eMsg = new Msg_J(Source, Parameters);
   	   	break;

   	   case Tokens::PART:
   	   	eMsg = new Msg_L(Source, Parameters);
   	   	break;

   	   case Tokens::SQUIT:
   	   	eMsg = new Msg_SQ(Source, Parameters);
   	   	break;


   	   // NOT USED YET...

   	   case Tokens::ACCOUNT:
   	   	break;

   	   case Tokens::NONE:
   	   	// Will be used in the future when done recognicing all tokens.
   	   	break;
   	   }

   	   

   	   if (NULL != eMsg)
    	   {
   	   	eMsg->Parser();
   	   	delete eMsg;
   	   	eMsg = NULL;
   	   	NotifyMonitors(eTokens->GetToken(Token), Source, Parameters);
   	   }

   	}
   	while (0 < InBuffer::ibInstance.count());
}


} // namespace eNetworks
