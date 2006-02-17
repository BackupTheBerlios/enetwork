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

#ifndef WIN32
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/poll.h>
#else
#include <direct.h>
#endif

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <list>

#include "BotCService.h"
#include "Network.h"
#include "tools.h"
#include "SocketException.h"
#include "Socket.h"
#include "tools.h"
#include "debug.h"
#include "ConfigParser.h"
#include "P10Tokens.h"
#include "InBuffer.h"
#include "MsgParseSystem.h"
#include "SqlManager.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;

using namespace eNetworks;

int main()
{
#ifndef WIN32

/*
   // Make a child, die and let initd take care of us. (send to background)
   if (0 == fork()) 
    setsid(); 
   else 
    exit(0);
*/

#else
	{
		char dir[200];
		cout << _getcwd(dir, 200) << endl;
		cout << dir << endl;
	}
#endif

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
   theConfigParser.InsertItem("MYSQLHOST");
   theConfigParser.InsertItem("MYSQLUSER");
   theConfigParser.InsertItem("MYSQLPASS");
   theConfigParser.InsertItem("MYSQLDB");
 
   theConfigParser.ParseConfigFile();

   // Connect to database server.
   SqlManager::connect( theConfigParser.GetConfiguration("MYSQLDB"),
   	   	   	theConfigParser.GetConfiguration("MYSQLHOST"),
   	   	   	theConfigParser.GetConfiguration("MYSQLUSER"),
   	   	   	theConfigParser.GetConfiguration("MYSQLPASS") );

   Network::Interface = Network(theConfigParser);

   // Login to server. Introduce the channels service bot and send EB (End of Burst). 
   login(theConfigParser);

   // Create Bots...
   {
   	new BotCService(theConfigParser);
   }

   // Add all the Tokens to the token map.
   eTokens = new Tokens();

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
   eTokens->AddToken("T",      Tokens::TOPIC);
   eTokens->AddToken("OM",     Tokens::OPMODE);
   eTokens->AddToken("P",      Tokens::PRIVMSG);
   eTokens->AddToken("O",      Tokens::NOTICE);
   eTokens->AddToken("D",      Tokens::KILL);

   // Inialize random seed.
   srand((clock() + time(0)) * 1000000);

   do
   {
	   // declaring fd_sets
	   fd_set Ofds; // Original
	   fd_set Cfds; // Copy
	   // initializing them
	   FD_ZERO(&Ofds);
	   FD_ZERO(&Cfds);
	   // setting them
	   FD_SET(Socket::eSock.GetSocket(), &Ofds);

	   struct timeval tv;
	   tv.tv_sec = 1;
	   tv.tv_usec = 1;
	
	   Cfds = Ofds; 
	   if (select(Socket::eSock.GetSocket()+1, &Ofds, NULL, NULL, &tv) == -1)
	   {
		   perror("select");
		   return 0;	
	   } 

	   static string inbuffer; // inbuffer needs a little bit of more global scope
	   if (FD_ISSET(Socket::eSock.GetSocket(), &Ofds))
	   {
		   InBuffer::ibInstance.insert(Socket::eSock.recv());
		   if (InBuffer::ibInstance.Digest())
			   MsgParseSystem::Execute();
	   }
  

   	// We're going to deal with timers here...
   } 
   while (Socket::eSock.is_valid());

return 0;
}
