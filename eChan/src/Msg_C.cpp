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
#include <cstdlib>
#include <iostream>

#include "Msg_C.h"
#include "Network.h"
#include "debug.h"
#include "tools.h"
#include "Client.h"
#include "Channel.h"
#include "MsgTokenizer.h"

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

   MsgTokenizer Channels(Parameters[0], NULL, ',');

   for (unsigned int i = 0; i < Channels.size(); i++)
   {
   	if (NULL == Network::Interface.FindChannel(Channels[i]))
   	{

   	   if (!Network::Interface.AddChannel(Channels[i], StringToInt(Parameters[1])))
   	   {
   	   	debug << "Could not add channel " << Channels[i] << endb;
   	   	exit(0);
   	   }
   	   else
   	   {
   	   	Network::Interface.FindChannel(Channels[i])->AddChannelClient(Network::Interface.FindClientByNumeric(Source.GetNumeric()), "o");
/*
   	   	cout << "Added Channel " << Channels[i] << " to db. And set client " << Source.GetName() << " as the creator "
   	   	     << "at TimeStamp " << Parameters[1] << endl;
*/
   	   }
   	}
   	else
    	{
   	   debug << "Error: Trying to create a channel that already exists." << endb;
   	}

   }
}

} // namespace eNetworks
