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

#include <pthread.h>
#include <iostream>

#include "Thread.h"
#include "InMsgSystem.h"
#include "Socket.h"
#include "InBuffer.h"

using std::cout;
using std::endl;

namespace eNetworks
{

void InMsgSystem::Execute()
{
   do
   {
   	pthread_mutex_lock(&MX_ESOCK);
   	pthread_cond_wait(&CV_NEW_IN_MSG, &MX_ESOCK);
   	string aNewMsg;
   	(*eSock) >> aNewMsg; // put it on a tmp buffer before we give it to InBuffer.
   	pthread_mutex_unlock(&MX_ESOCK);

   	// lets give it to InBuffer.
   	pthread_mutex_lock(&MX_EINBUFFER); // get access to InBuffer.
   	eInBuffer->insert(aNewMsg);
   	if (eInBuffer->Digest())
   	{
   	   pthread_mutex_unlock(&MX_EINBUFFER);
   	   pthread_cond_signal(&CV_NEW_CMD);
   	}
   	else
   	{
   	   pthread_mutex_unlock(&MX_EINBUFFER);
   	}

   } while (true);

}

} // namespace eNetworks
