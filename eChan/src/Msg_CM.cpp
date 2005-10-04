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

#include "Msg_CM.h"
#include "Server.h"
#include "P10Tokens.h"
#include "debug.h"
#include "Channel.h"
#include "Network.h"

using std::cout;
using std::endl;

namespace eNetworks
{

void Msg_CM::Parser()
{
   if (Source.IsSourceless())
   	debug << "Warning: CLEARMODE message without source." << endb;

   Channel* theChannel = eNetwork->FindChannel(Parameters[0]);
   if (NULL == theChannel)
   {
   	debug << "Cannot find channel " << Parameters[0] << " in CM message." << endb;
   	exit(0);
   }

   for (unsigned int i = 0; i < Parameters[1].length(); i++)
   {
   	switch(Parameters[1][i])
   	{
   	   case 'o':
   	   	theChannel->ClearOps();
   	   	break;

   	   case 'v':
   	   	theChannel->ClearVoice();
   	   	break;

   	   case 'b':
   	   	theChannel->ClearBans();
   	   	break;

   	   case 'l':
   	   	theChannel->UnSetLimit();
   	   	break;

   	   case 'k':
   	   	theChannel->UnSetKey();
   	   	break;

   	   default:
   	   	theChannel->UnSetMode(Parameters[1][i]);
   	   	break;
   	}
   }
   cout << Source.GetName() << " performed a clearmode in channel " << Parameters[0] << " (" << Parameters[1] << ")." << endl;

}

} // namespace eNetworks

