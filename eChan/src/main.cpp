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
#include <ctime>
#include <list>

#include "Network.h"
#include "tools.h"
#include "SocketException.h"
#include "Socket.h"
#include "tools.h"
#include "debug.h"
#include "ConfParser.h"
#include "Msg.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::list;

using namespace eNetworks;

int main()
{
   // Make a child, die and let initd take care of it.
   if (0 == fork()) 
    setsid(); 
   else 
    exit(0);

   eNetwork = new Network;
   if (eNetwork == NULL)
   {
   	cout << "Could not allocate memory for Network class" << endl;
   	exit(0);
   }

   // Create LocalServer and LocalClient.
   CreateLocals();

   // Login to server. Introduce the channels service bot and send EB (End of Burst). 
   login();

   do
   {
	// declaring fd_sets
	fd_set Ofds; // Original
	fd_set Cfds; // Copy
	// initializing them
	FD_ZERO(&Ofds);
	FD_ZERO(&Cfds);
	// setting them
	FD_SET(eSock->GetSocket(), &Ofds);

	struct timeval tv;
	tv.tv_sec = 1;
	tv.tv_usec = 1;

	Cfds = Ofds; 
	if (select(eSock->GetSocket()+1, &Ofds, NULL, NULL, &tv) == -1)
	{
	   perror("select");
	   return 0;
	} 

	static string inbuffer; // inbuffer needs a little bit of more global scope
	if (FD_ISSET(eSock->GetSocket(), &Ofds))
	{
	   string tmp = "";
	   try 
	   {
	   	(*eSock) >> tmp;
	   }
	   catch(SocketException &sockerr)
	   {
	   	sockerr.log();
	   	sockerr.fix();
	   }

	   inbuffer += tmp;
	}

	// If we get a complete message: parse it.
	string command = "";
	while (IsCommand(inbuffer, command))
	{
   	   Msg *eMsg = Msg::MsgParser(command);
   	   if (eMsg == NULL)
   	   {
   	   	debug << "Got NULL after MsgParser()" << endb;
   	   	exit(0);
   	   }

   	   eMsg->Parser();
   	   delete eMsg;
   	   eMsg = NULL;
	}
   } 
   while (eSock->is_valid());

return 0;
}
