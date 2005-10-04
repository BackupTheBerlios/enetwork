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
#include <string>
#include <cstdlib>
#include <cstdio>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/poll.h>
#include <ctime>
#include <list>

#include "Network.h"
#include "tools.h"
#include "SocketException.h"
#include "Socket.h"
#include "tools.h"
#include "debug.h"
#include "ConfigParser.h"
#include "Msg.h"
#include "InBuffer.h"
#include "OutBuffer.h"
#include "Thread.h"
#include "P10Tokens.h"
#include "InMsgSystem.h"
#include "OutMsgSystem.h"
#include "MsgParseSystem.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;

using namespace eNetworks;

int main()
{

   // Make a child, die and let initd take care of us. (send to background)
   if (0 == fork()) 
    setsid(); 
   else 
    exit(0);

   ConfigParser theConfigParser;

   // add configuration items.
   theConfigParser.InsertItem("NICK");
   theConfigParser.InsertItem("NUMERIC");
   theConfigParser.InsertItem("USERNAME");
   theConfigParser.InsertItem("SERVERNAME");
   theConfigParser.InsertItem("CLIENTINFO");
   theConfigParser.InsertItem("HOSTNAME");
   theConfigParser.InsertItem("SERVERINFO");
   theConfigParser.InsertItem("UPLINK");
   theConfigParser.InsertItem("PORT");
   theConfigParser.InsertItem("LINKPASS");

   theConfigParser.ParseConfigFile();

   eNetwork = new Network(theConfigParser);
   if (eNetwork == NULL)
   {
   	debug << "Could not allocate memory for Network class" << endb;
   	exit(0);
   }

   eInBuffer = new InBuffer();
   eOutBuffer = new OutBuffer();

   // Login to server. Introduce the channels service bot and send EB (End of Burst). 
   login(theConfigParser);

   // Add all the Tokens to the token map.
   eTokens = new Tokens();

   // Create Threads...
   cout << "Creating new Threads..." << endl;
   InMsgSystem eInMsgSystem;
   eInMsgSystem.Start();

   OutMsgSystem eOutMsgSystem;
   eOutMsgSystem.Start();

   MsgParseSystem eParseMsgSystem;
   eParseMsgSystem.Start();

   if (NULL == eTokens)
   {
   	debug << "Could not allocate memory for tokens" << endb;
   }

   // Register Server Messages (Tokens)
   eTokens->AddToken("S",      Tokens::SERVER); // Server introducing another server to the network.
   eTokens->AddToken("N",      Tokens::NICK);
   eTokens->AddToken("B",      Tokens::B);
   eTokens->AddToken("BURST",  Tokens::BURST);
   eTokens->AddToken("J",      Tokens::JOIN);
   eTokens->AddToken("L",      Tokens::PART);
   eTokens->AddToken("G",      Tokens::PING);
   eTokens->AddToken("EB",     Tokens::END_OF_BURST); 
   eTokens->AddToken("AC",     Tokens::ACCOUNT);
   eTokens->AddToken("C",      Tokens::CREATE);
   eTokens->AddToken("Q",      Tokens::QUIT);
   eTokens->AddToken("SQ",     Tokens::SQUIT);
   eTokens->AddToken("M",      Tokens::MODE);
   eTokens->AddToken("K",      Tokens::KICK);
   eTokens->AddToken("CM",     Tokens::CLEARMODE);

   pollfd PollFD;
   PollFD.fd = eSock->GetSocket();
   PollFD.events = POLLIN;

   do
   {
   	if (poll(&PollFD, 1, -1) == 1 && (PollFD.revents == POLLIN || PollFD.revents == POLLPRI))
   	{
   	   pthread_cond_signal(&CV_NEW_IN_MSG);
   	}

   	// We're going to deal with timers here...
   } 
   while (eSock->is_valid());

return 0;
}
