/*
 * eChan - Electronic Channel Services.
 * Copyright (C) 2003 Alan Alvarez.
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

#include <netinet/in.h>
#include <string>

namespace eNetworks
{

const int MAXHOSTNAME = 200;
const int MAXRECV = 800;

class Socket
{
   public:
	Socket(const std::string &host, const int port);
	~Socket();

	bool is_valid() const { return sockfd != -1; }
	int GetSocket() { return sockfd; } 

	const Socket &operator<<(const std::string &outbuff ) const;
	const Socket &operator<<(const int &intbuff) const;
	const Socket &operator>>(std::string &inbuff) const;

   private:

	int sockfd;
	sockaddr_in m_addr;
};

extern Socket *eSock;

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__SOCKET_H
