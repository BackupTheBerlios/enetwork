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

#include <string>
#include <cstdlib>
#include <iostream>

#include "Msg_C.h"
#include "Network.h"
#include "debug.h"
#include "tools.h"
#include "Client.h"
#include "Channel.h"

using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

//              Token
// example: ABAAA C #c++ 1109184912
//          Client  Channel    TimeStamp

void Msg_C::Parser()
{
   // If channel doesn't exist then create it.
   if (eNetwork->FindChannel(Parameters[0]) == NULL)
   {
   	if (!eNetwork->AddChannel(Parameters[0], StringToInt(Parameters[1])))
   	{
   	   debug << "Could not add channel " << Parameters[0] << endb;
   	   exit(0);
   	}


   	Channel *aChannel =  eNetwork->FindChannel(Parameters[0]);


   	if (aChannel != NULL)
   	{
   	   // Add the client that created the channel and give +o
   	   aChannel->AddChannelClient(eNetwork->FindClientByNumeric(ClientSrc->GetNumeric()), "o"); 
   	}

   	cout << "Added Channel " << aChannel->GetName() << " to db. and set client " 
             << eNetwork->FindClientByNumeric(ClientSrc->GetNumeric())->GetNickName()
   	     << " as the creator at TimeStamp: " << Parameters[1] << endl;


   }
   else 
   // Something went wrong here because we never create channels unless eChan is asked to join an empty channel and that has not been implemented yet.
   {
   	debug << "Error: Trying to create a channel that already exists." << endb;
   }

}

} // namespace eNetworks
