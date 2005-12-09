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

#ifndef ELECTRONIC_NETWORKS__SOCKET_H
#define ELECTRONIC_NETWORKS__SOCKET_H

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string>

#include "SocketException.h"
#include "tools.h"

namespace eNetworks
{

const int MAXHOSTNAME = 200;
const int MAXRECV = 800;

class Socket
{
   public:
   	Socket() : sockfd(-1) {}; // Default constructor. 

	~Socket()
   	{
   	   if (is_valid())
   	   	close(sockfd);
   	}

   	// return whether we're connected or not.
	bool is_valid() const { return sockfd != -1; }

   	// Get the socket file descriptor.
	int GetSocket() { return sockfd; } 

   	// connect to uplink.
   	void connect(const std::string& host, const int& port);

   	// returns recieved message.
   	std::string recv() const;

   	// send a message to the uplink.
   	void send(const std::string &msg) const
   	{
   	   if (::send(sockfd, msg.c_str(), msg.size(), 0) == -1)
   	   	throw SocketException("Error while sending message", SocketException::SEND);
   	}

	const Socket &operator<<(const std::string &outbuff ) const
   	{
   	   send(outbuff);
   	   return *this;
   	}

	const Socket &operator<<(const int &intbuff) const
   	{
   	   send(IntToString(intbuff));
   	   return *this;
   	}

	const Socket &operator>>(std::string &inbuff) const
   	{
   	   inbuff = recv();
   	   return *this;
   	}

   	static Socket eSock;

   private:

	int sockfd;
//   	string hostname;
//   	string ip;
//   	unsigned short port;
	sockaddr_in m_addr;
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__SOCKET_H
