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
   else if (Token == Tokens::ERROR)
   {
   	debug << aCommand;
   	exit(0);
   }
   else
   {    
   	if (aCommand.length() > aCommand.find(Token)+1+Token.length())
   	{
   	   Parameters = aCommand.substr(aCommand.find(Token)+Token.length());
//   	   cout << "Parameters[0]: " << Parameters[0] << endl;
   	}

   	if (aCommand.find(' ') == 2) // This message came from a server.
   	{
   	   ServerSrc = eNetwork->FindServerByNumeric(aCommand.substr(0,2));
    	   ClientSrc = NULL;
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
   string Description;
   if (Parameters.size() == 8)
   {
    	if (Parameters[6][0] == '+' && Parameters[6].size() > 1)
   	 Flag = Parameters[6][1];

   	Description = Parameters[7];
   }
   else 
    Description = Parameters[6];

   if (!eNetwork->AddServer(Numeric, Name, LocalServer->GetNumeric(), Description, StartTime, LinkTime, HopCount, Flag))
   {
   	debug << "Could not add Server Name";
   	exit(0);
   }
  
   cout << "Added Server Name: " << Name << " Numeric: " << Numeric << " StartTime: " << StartTime <<  
           " LinkTime: " << LinkTime << " HopCount: " << HopCount << " Flag: " << Flag << endl << 
           "Description: " << Description << endl;

}

// ========
//  Msg_S
// ========

void Msg_S::Parser()
{

   if (ServerSrc == NULL)
   {
        debug << "Protocol Violation. Token S with no source.";
        exit(0);
   }

   if (Parameters.size() < 6 && Parameters.size() > 8)
   {
        debug << "Protocol Violation: Too Many Parameters in Msg_S::Parser()";
        exit(1);
   }

   string Name = Parameters[0];

   unsigned int HopCount;
   if (StringToInt(Parameters[1]) < 2)
   {
        debug << "Protocol Violation: Hop Count shouldn't be less than 2 in Msg_S::Parser()";
        exit(1);
   }
   else
    HopCount = StringToInt(Parameters[1]);

   time_t StartTime;
   if (!IsDigit(Parameters[2]))
   {
        debug << "Protocol Violation: StartTime should be only digit numbers in Msg_S::Parser()";
        exit(1);
   }
   else
    StartTime = StringToInt(Parameters[2]);

   time_t LinkTime;
   if (!IsDigit(Parameters[3]))
   {
        debug << "Protocol Violation: LinkTime should be only digit numbers in Msg_S::Parser()";
        exit(1);
   }
   else
    LinkTime = StringToInt(Parameters[3]);

   if (Parameters[4] != "P10")
   {
        debug << "Protocol Violation: Protocol should be P10 in Msg_S::Parser()";
        exit(1);
   }

   string B64IP = Parameters[4];

   string Numeric = Parameters[5].substr(0,2);

   char Flag = '0';
   string Description;
   if (Parameters.size() == 8)
   {
        if (Parameters[6][0] == '+' && Parameters[6].size() > 1)
         Flag = Parameters[6][1];

        Description = Parameters[7];
   }
   else
    Description = Parameters[6];

   if (!eNetwork->AddServer(Numeric, Name, ServerSrc->GetNumeric(), Description, StartTime, LinkTime, HopCount, Flag))
   {
        debug << "Could not add Server Name";
        exit(0);
   }

   cout << "Added Server Name: " << Name << " Numeric: " << Numeric << " StartTime: " << StartTime <<
           " LinkTime: " << LinkTime << " HopCount: " << HopCount << " Flag: " << Flag << " Uplink: " <<
           ServerSrc->GetNumeric() << endl <<  "Description: " << Description << endl;

}

// ========
//  Msg_N
// ========

void Msg_N::Parser()
{

   if (Parameters.size() < 7 || Parameters.size() > 9)
   {
   	debug << "Protocol Violation: error on number of arguments in Msg_N::Parser()";
   	exit(0);
   }

   if (ServerSrc == NULL)
   {
        debug << "Protocol Violation. Token N with no source.";
        exit(0);
   }

   string NickName = Parameters[0];

   unsigned int HopCount = StringToInt(Parameters[1]);

   if (HopCount < 1)
   {
   	debug << "Protocol violation: HopCount cannot be less than 1 in Msg_S::parser()";
   	exit(0);
   }

   time_t TimeStamp;
   if (!IsDigit(Parameters[2]))
   {
   	debug << "TimeStamp can only have digit numbers in function Msg_S::parser()";
   	exit(0);
   }
   else
    TimeStamp = StringToInt(Parameters[2]);

   string UserName = Parameters[3];
   string HostName = Parameters[4];

   string Modes = "";
   string Account = "";
   string B64IP = "";
   string Numeric = "";   
   string UserInfo = "";

   if (Parameters[5][0] == '+')
   {
   	Modes = Parameters[5].substr(1);
   	if (Modes.find("r") != string::npos)
   	{
   	   Account = Parameters[6];
   	   B64IP = Parameters[7];
   	   Numeric = Parameters[8];
   	   if (Parameters.size() == 10)
   	    UserInfo = Parameters[9];
   	}

   	B64IP = Parameters[6];
   	Numeric = Parameters[7];
   	if (Parameters.size() == 9)
   	 UserInfo = Parameters[8];
   }
   else
   {
   	B64IP = Parameters[5];
   	Numeric = Parameters[6];
   	if (Parameters.size() == 8)
   	 UserInfo = Parameters[7];
   }

   if (!eNetwork->AddClient(Numeric, NickName, Account, UserName, HostName, B64IP, Modes, UserInfo, TimeStamp, HopCount))
   {
   	debug << "Could not add client " << NickName << " with Numeric " << Numeric;
   	exit(0);
   }

   cout << "Added Client with Numeric: " << Numeric << " NickName: " << NickName << " Account: " << Account <<
           " UserName: " << UserName << " HostName: " << HostName << " B6IP: " << B64IP << " Modes: " << Modes <<
           " TimeStamp: " << TimeStamp << " HopCount: " << HopCount << endl << "UserInfo: " << UserInfo << endl;

}

} // namespace eNetworks
