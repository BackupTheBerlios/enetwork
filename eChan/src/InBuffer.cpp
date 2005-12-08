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
#include <pthread.h>
#include <iostream>
#include "tools.h"

#include "Thread.h"
#include "InBuffer.h"
#include "debug.h"

using std::cout;
using std::endl;

namespace eNetworks {


bool InBuffer::Digest()
{
   bool Digested = false;
   while (buffer.find('\n') != string::npos || buffer.find("\r\n") != string::npos || buffer.find('\r') != string::npos)
   {

   	// Get rid of empty messages.
   	while ('\r' == buffer[0] || '\n' == buffer[0])
   	{
   	   buffer = buffer.substr(1);
   	}

        if (buffer.find("\r\n") != string::npos)
        {
           Msgs.push_back(buffer.substr(0,buffer.find("\r\n")));
           buffer = buffer.substr(buffer.find("\r\n")+2);
           Digested = true;
        }
        else if (buffer.find('\n') != string::npos)
        {
           Msgs.push_back(buffer.substr(0,buffer.find('\n')));
           buffer = buffer.substr(buffer.find('\n')+1);
   	   Digested = true;
        }
   	else if (buffer.find('\r') != string::npos)
   	{
   	   Msgs.push_back(buffer.substr(0,buffer.find('\r')));
   	   buffer = buffer.substr(buffer.find('\r')+1);
   	   Digested = true;
   	}
   }
  
   return Digested;
}

InBuffer InBuffer::ibInstance = InBuffer();

} // namespace eNetworks
