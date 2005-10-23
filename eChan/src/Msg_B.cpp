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

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "debug.h"
#include "Msg_B.h"
#include "tools.h"
#include "Channel.h"
#include "Client.h"
#include "Network.h"

using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

// ========
//  Msg_B
// ========

void Msg_B::Parser()
{

   if (Parameters.size() < 3)
   {
   	debug << "Protocol Violation: error on number of arguments in Msg_B::Parser()" << endb;
   	exit(0);
   }

   string Name = Parameters[0];

   if (!IsDigit(Parameters[1]))
   {
        debug << "Protocol Violation: TimeStamp should only contain digits in Msg_B::Parser()" << endb;
        exit(0);
   }

   Channel *ChannelPtr = Network::Interface.FindChannel(Name);
   // This is a new channel.
   if (NULL == ChannelPtr)
   {

   	time_t TimeStamp = StringToInt(Parameters[1]);

   	string Modes = "";
   	string Key = "";
   	unsigned int Limit = 0;

   	if (Parameters[2][0] == '+')
   	{
           Modes = Parameters[2].substr(1);
           if (Modes.find('k') != string::npos && Modes.find('l') != string::npos)
           {
   	   	if (Modes.find('l') < Modes.find('k'))
   	   	{
   	   	   Limit = StringToInt(Parameters[3]);
   	   	   Key = Parameters[4];
   	   	}
   	   	else
   	   	{
   	   	   Key = Parameters[3];
   	   	   Limit = StringToInt(Parameters[4]);
   	   	} 

   	   }
	   else if (Modes.find('l') != string::npos || Modes.find('k') != string::npos)
   	   {
   	   	if (Modes.find('l') != string::npos)
   	   	{
   	   	   Limit = StringToInt(Parameters[3]);
   	   	}
   	   	else
   	   	{
   	   	   Key = Parameters[3];
   	   	}
   	   }

   	}

   	if (!Network::Interface.AddChannel(Name, TimeStamp, "", Modes, Key, Limit))
   	{
   	   debug << "Could not add channel " << Name  << " in Msg_B::Parser()." << endb;
   	   exit(0);
   	}
   
  
   	cout << "Added channel with Name: " << Name << " Modes: " << Modes << " Key: " << Key << " Limit: "
             << Limit << " TimeStamp: " << TimeStamp << endl;
  

   	ChannelPtr = Network::Interface.FindChannel(Name);
   	if (ChannelPtr == NULL)
   	{
   	   debug << "Could not find channel " << Name  << " in Msg_B::Parser()." << endb;
   	   exit(0);
   	}

   }

   // if last parameter is bans '%'
   if (Parameters[Parameters.size()-1][0] == '%')
   {
   	ParseBans(ChannelPtr, Parameters[Parameters.size()-1]);
   	ParseUsers(ChannelPtr, Parameters[Parameters.size()-2]);
   }
   else
   {
   	ParseUsers(ChannelPtr, Parameters[Parameters.size()-1]);
   }
}

void Msg_B::ParseUsers(Channel *aChannelPtr, const std::string &UsersParameters)
{
   string CurrentMode;

   MsgTokenizer Users(UsersParameters,',');

   for (unsigned int i = 0; i < Users.size(); i++)
   {
   	Client * ClientPtr = Network::Interface.FindClientByNumeric(Users[i].substr(0,5));
   	if (ClientPtr == NULL)
   	{
   	   debug << "Could not add Client " << Users[i].substr(0,5) << " to channel " << aChannelPtr->GetName() << endb;
   	   exit(0);
   	}

   	if (Users[i].size() == 5)
   	{
   	   aChannelPtr->AddChannelClient(ClientPtr, CurrentMode);
   	   
   	   cout << "Added Client " << ClientPtr->GetNickName() << " to " << aChannelPtr->GetName() << 
   	           " with mode " << CurrentMode << endl;
   	   
   	}
   	else if (Users[i].size() == 7 || Users[i].size() == 8)
   	{
   	   CurrentMode = Users[i].substr(6);
   	   aChannelPtr->AddChannelClient(ClientPtr, CurrentMode);
   	   
   	   cout << "Added Client " << ClientPtr->GetNickName() << " to " << aChannelPtr->GetName() << 
   	           " with mode " << CurrentMode << endl;
   	   
   	}
   }
} 

void Msg_B::ParseBans(Channel *aChannelPtr, const std::string &BansParameters)
{
   MsgTokenizer Bans(BansParameters.substr(1));

   for (unsigned int i = 0; i < Bans.size(); i++)
   {
	cout << "Added Ban: " << Bans[i] << endl;
   	aChannelPtr->AddBan(Bans[i]);
   }
}

// =============
//   Msg_BURST
// =============

void Msg_Burst::Parser()
{
   Channel *ChannelPtr = Network::Interface.FindChannel(Parameters[0]);

   // if last parameter is bans '%'
   if (Parameters[Parameters.size()-1][0] == '%')
   {
        ParseBans(ChannelPtr, Parameters[Parameters.size()-1]);
        ParseUsers(ChannelPtr, Parameters[Parameters.size()-2]);
   }
   else
   {
        ParseUsers(ChannelPtr, Parameters[Parameters.size()-1]);
   }


}

} // namespace eNetworks
