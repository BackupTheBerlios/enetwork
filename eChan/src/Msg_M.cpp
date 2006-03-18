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

#include <string>
#include <iostream>
#include <map>

#include "Msg_M.h"
#include "Socket.h"
#include "Server.h"
#include "P10Tokens.h"
#include "OutBuffer.h"
#include "Network.h"
#include "debug.h"
#include "Client.h"
#include "tools.h"
#include "Channel.h"
#include "ChannelClient.h"


using std::string;
using std::cout;
using std::endl;
using std::map;

namespace eNetworks
{

void Msg_M::Parser()
{
   if ('#' == Parameters[0][0])
   {
   	// This is a channel Mode.
   	Channel* theChannel = Network::Interface.FindChannel(Parameters[0]);
   	if (NULL == theChannel)
   	   debug << "Cannot find Channel " << Parameters[0] << ". in Mode message." << endb;

   	bool bAdd = true;
   	unsigned int intCurrentParameter = 1;

   	for (unsigned int i = 0; i < Parameters[1].length(); i++)
   	{
   	   ChannelClient* theChannelClient = NULL;
   	   switch(Parameters[1][i])
   	   {
   	   	case '+':
   	   	   bAdd = true;
   	   	   break;

   	   	case '-':
   	   	   bAdd = false;
   	   	   break;

   	   	case 'l':
   	   	   if (bAdd)
   	   	   {
   	   	   	theChannel->SetLimit(StringToInt(Parameters[++intCurrentParameter]));
   	   	   	// intCurrentParameter++;
   	   	   }
   	   	   else
   	   	   {
   	   	   	theChannel->UnSetLimit();
   	   	   }
   	   	   break;

   	   	case 'k':
   	   	   if (bAdd)
   	   	   {
   	   	   	theChannel->SetKey(Parameters[intCurrentParameter+1]);
   	   	   	intCurrentParameter++;
   	   	   }
   	   	   else
   	   	   {
   	   	   	theChannel->UnSetKey();
   	   	   	intCurrentParameter++;
   	   	   }
   	   	   	break;

   	   	case 'b':
   	   	   if (bAdd)
   	   	   {
   	   	   	theChannel->AddBan(Parameters[++intCurrentParameter]);
   	   	   	// intCurrentParameter++;
   	   	   }
   	   	   else
   	   	   {
   	   	   	theChannel->DelBan(Parameters[++intCurrentParameter]);
   	   	   	// intCurrentParameter++;
   	   	   }

   	   	   break;
   	   	   
   	   	// user modes.
   	   	case 'o':
   	   	case 'v':

   	   	   theChannelClient = theChannel->FindChannelClient(Parameters[intCurrentParameter+1]);
   	   	   if (NULL == theChannelClient)
   	   	   {
   	   	   	debug << "Cannot find ChannelClient " << Parameters[intCurrentParameter+1] << ". in Mode message." << endb;
   	   	   	break;
   	   	   }
   	   	   	   
   	   	   if (bAdd)
   	   	   {
   	   	   	theChannelClient->AddMode(Parameters[1][i]);
   	   	   }
   	   	   else
   	   	   {
   	   	   	theChannelClient->DelMode(Parameters[1][i]);
   	   	   }
   	   	    
   	   	   intCurrentParameter++;

   	   	   theChannelClient = NULL;
   	   	   break;

   	   	default:
   	   	   if (bAdd)
   	   	   {
   	   	   	theChannel->SetMode(Parameters[1][i]);
   	   	   }
   	   	   else
   	   	   {
   	   	   	theChannel->UnSetMode(Parameters[1][i]);
   	   	   }

   	   	   break;
   	   }   
   	}
   }
   else
   {
   	// This is a user mode.
   	Client* theClient = Network::Interface.FindClientByNickName(Parameters[0]);
   	if (NULL == theClient)
   	   debug << "Cannot find client " << Parameters[0] << ". in Mode message." << endb;

   	bool bAdd = true;
   	for (unsigned int i = 0; i < Parameters[1].length(); i++)
   	{
   	   switch(Parameters[1][i])
   	   {
   	   	case '+':
   	   	   bAdd = true;
   	   	   break;

   	   	case '-':
   	   	   bAdd = false;
   	   	   break;

   	   	default:
  	   	   if (bAdd)
   	   	   {
   	   	   	theClient->AddMode(Parameters[1][i]);
   	   	   }
   	   	   else
   	   	   {
   	   	   	theClient->DelMode(Parameters[1][i]);
   	   	   }
   	   	   break;
   	   }
   	}
   }
}

} // namespace eNetworks
