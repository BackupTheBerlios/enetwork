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
#include "OutMsgSystem.h"
#include "OutBuffer.h"
#include "Socket.h"

using std::cout;
using std::endl;

namespace eNetworks
{

void OutMsgSystem::Execute()
{
   do
   {
   	pthread_mutex_lock(&MX_EOUTBUFFER);
   	pthread_cond_wait(&CV_NEW_OUT_MSG, &MX_EOUTBUFFER);
   	pthread_mutex_unlock(&MX_EOUTBUFFER);

   	std::string buf = eOutBuffer->pop();
   	(*eSock) << buf << "\n";
   	cout << "[OUT]: " << buf << endl;

   } while (true);



}

} // namespace eNetworks
