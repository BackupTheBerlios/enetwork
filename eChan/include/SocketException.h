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

#ifndef ELECTRONIC_NETWORKS__SOCKETEXCEPTION_H
#define ELECTRONIC_NETWORKS__SOCKETEXCEPTION_H

#include <string>

#include "debug.h"

namespace eNetworks
{

class SocketException
{
   public:
	SocketException(const std::string &errarg, const unsigned int &functionarg) : error(errarg), function(functionarg) 
        {};
	~SocketException(){};

	void log() const { debug << error << endb; }

	unsigned int GetFunction() const { return function; } 
	std::string GetError() const { return error; }
	
	void fix();

	// Functions causing errors
	static const unsigned SOCKET;
	static const unsigned SETSOCKOPT;
 	static const unsigned CONNECT;
 	static const unsigned SEND;
	static const unsigned RECV;


   private:

	const std::string error;
	const unsigned int function;

};

} // namespace eNetworks.

#endif // ELECTRONIC_NETWORKS__SOCKETEXCEPTION_H
