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

#ifndef ELECTRONIC_NETWORKS__THREADEXCEPTION_H
#define ELECTRONIC_NETWORKS__THREADEXCEPTION_H

#include <string>

using std::string;

namespace eNetworks
{

class ThreadException
{
   public:
   	enum ID { THREAD_ALREADY_EXIST = 0, THREAD_NO_ENOUGH_RESOURCES };

   	ThreadException (const ID &aID) : theID(aID) {}

   private:
   	ID theID;
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__THREADEXCEPTION_H
