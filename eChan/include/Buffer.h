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

#ifndef ELECTRONIC_NETWORKS__BUFFER_H
#define ELECTRONIC_NETWORKS__BUFFER_H

#include <string>
#include <list>
#include <iostream>

using std::string;
using std::list;
using std::cout;
using std::endl;

namespace eNetworks
{

class Buffer
{
   public:
   	// Constructor
   	Buffer() : Msgs() {}

   	virtual ~Buffer() {}

   	// returns size of buffer.
   	const unsigned int count() const { return Msgs.size(); }

   	// Insert message to the buffer.
   	virtual void insert(const std::string& _Msg) = 0;

   	// pop a message from the buffer.
   	string pop()
   	{
   	   if (0 < count())
   	   {
   	   	string retval = Msgs.front(); // Get the First Msg in the list.
   	   	Msgs.pop_front(); // Pop it out of the list.
   	   	return retval;
   	   }
   	   
   	   return ""; // This represents an error.
   	}


   protected:
   	list<string> Msgs; // This is a list that holds a collection of messages waiting to be used.
};

}

#endif // ELECTRONIC_NETWORKS__BUFFER_H
