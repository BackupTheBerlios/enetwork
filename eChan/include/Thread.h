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

#ifndef ELECTRONIC_NETWORKS__THREAD_H
#define ELECTRONIC_NETWORKS__THREAD_H

#include <pthread.h>

namespace eNetworks
{

class Thread
{
   public:
   	Thread() : ThreadID() {}
   	virtual ~Thread() {}

   	virtual bool Start();
   	virtual void Execute() = 0;
 	

   private:
   	pthread_t ThreadID;

   protected:
   	void exit(void *retrval) const { ::pthread_exit(retrval); }
};

/*
// Mutex for these global objects.
extern pthread_mutex_t MX_EINBUFFER;
extern pthread_mutex_t MX_EOUTBUFFER;
extern pthread_mutex_t MX_ESOCK;

// Condition Variables.
extern pthread_cond_t CV_NEW_IN_MSG;
extern pthread_cond_t CV_NEW_OUT_MSG;
extern pthread_cond_t CV_NEW_CMD;
*/

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__THREAD_H
