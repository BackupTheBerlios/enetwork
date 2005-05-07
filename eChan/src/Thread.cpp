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
#include <errno.h>
#include <iostream>

extern int errno;

#include "Thread.h"
#include "ThreadException.h"

using std::cout;
using std::endl;

namespace eNetworks
{

#ifdef __cplusplus
extern "C" void* NewThread(void* thread)
{
   Thread *eThread = static_cast<Thread*>(thread);
   eThread->Execute();

   return 0;
}
#endif

bool Thread::Start()
{
   if (::pthread_create(&ThreadID, NULL, NewThread, static_cast<void*>(this)) != 0)
   {
   	throw ThreadException(ThreadException::THREAD_NO_ENOUGH_RESOURCES);   	
   	return false;
   }

return true;
}

// Initialization of Mutexes.
pthread_mutex_t MX_EINBUFFER = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t MX_EOUTBUFFER = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t MX_ESOCK = PTHREAD_MUTEX_INITIALIZER;

// Initialization of Condition Variables.
pthread_cond_t CV_NEW_IN_MSG = PTHREAD_COND_INITIALIZER;
pthread_cond_t CV_NEW_OUT_MSG = PTHREAD_COND_INITIALIZER;
pthread_cond_t CV_NEW_CMD = PTHREAD_COND_INITIALIZER;

} // namespace eNetworks
