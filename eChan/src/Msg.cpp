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
   else
   {    
   	Parameters = aCommand.substr(aCommand.find(Token)+2);

   	if (aCommand.find(' ') == 2) // This message came from a server.
   	{
   	   ServerSrc = eNetwork->FindServerByNumeric(aCommand.substr(0,2));
 
   	   if (ServerSrc == NULL)
   	   {
   	   	debug << "Can't find Server " << aCommand.substr(0,2) << " in my database";
   	   	exit(0);
   	   }
   	}
   	else if (aCommand.find(' ') == 5)
   	{
   	   ClientSrc = eNetwork->FindClientByNumeric(aCommand.substr(0,5)); 

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

// ==============
//  PreServerMsg
// ==============

void PreServerMsg::Parser()
{
   if (Parameters.size() < 6 && Parameters.size() > 8)
   {
   	debug << "Protocol Violation: Too Many Parameters in PreServerMsg::Parser()";
   	exit(1);
   }

   string Name = Parameters[0]; 

   unsigned int HopCount;
   if (Parameters[1] != "1")
   {
   	debug << "Protocol Violation: Hop Count should be 1 in PreServerMsg::Parser()";
   	exit(1);
   }
   else
    HopCount = StringToInt(Parameters[1]);

   time_t StartTime;
   if (!IsDigit(Parameters[2]))
   {
   	debug << "Protocol Violation: StartTime should be only digit numbers in PreServerMsg::Parser()";
   	exit(1);
   }
   else
    StartTime = StringToInt(Parameters[2]);

   time_t LinkTime;
   if (!IsDigit(Parameters[3]))
   {
        debug << "Protocol Violation: LinkTime should be only digit numbers in PreServerMsg::Parser()";
        exit(1);
   }
   else
    LinkTime = StringToInt(Parameters[3]);
 
   if (Parameters[4] != "J10")
   {
   	debug << "Protocol Violation: Protocol should be J10 at link time in PreServerMsg::Parser()";
   	exit(1);
   }
   
   string B64IP = Parameters[4];
  
   // ignore Parameters[5]

   string Numeric = Parameters[5].substr(0,2);

   char Flag = '0';
   if (Parameters.size() == 8)
   {
    	if (Parameters[6][0] == '+' && Parameters[6].size() > 1)
   	 Flag = Parameters[6][1];
   }

   string Description = Parameters[8];

   if (!eNetwork->AddServer(Numeric, Name, LocalServer->GetNumeric(), Description, StartTime, LinkTime, HopCount, Flag))
   {
   	debug << "Could not add Server Name";
   	exit(0);
   }
  
   cout << "Added Server Name: " << Name << " Numeric: " << Numeric << " StartTime: " << StartTime <<  
           " LinkTime: " << LinkTime << " HopCount: " << HopCount << " Flag: " << Flag << endl << 
           "Description: " << Description << endl;

}

} // namespace eNetworks
