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

#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>

#include "tools.h"
#include "SocketException.h"
#include "Socket.h"

using std::string;

namespace eNetworks
{

Socket::Socket(const string &host, const int port) : sockfd(-1)
{
   ::memset(&m_addr, 0, sizeof(m_addr));

   sockfd = ::socket(AF_INET, SOCK_STREAM, 0);

   if (!is_valid())
    throw SocketException("Could not create socket", SocketException::SOCKET);

   // TIME_WAIT - argh
   int on = 1;
   if (::setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*) &on, sizeof(on)) == -1)
    throw SocketException("Could not re-use socket address", SocketException::SETSOCKOPT);

   m_addr.sin_family = AF_INET;
   m_addr.sin_port = ::htons(port);

   ::inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);

   if (::connect (sockfd, (sockaddr *) &m_addr, sizeof(m_addr)) == -1)
   {
	if (errno == EISCONN)
	 throw SocketException("This socket is already connected", SocketException::CONNECT);
	else if (errno == ECONNREFUSED)
	 throw SocketException("Connection refused", SocketException::CONNECT);
	else if (errno == ETIMEDOUT)
	 throw SocketException("Connection timed out", SocketException::CONNECT);
	else if (errno == ENETUNREACH)
	 throw SocketException("Network is unreachable", SocketException::CONNECT);
	else if (errno == EADDRINUSE)
	 throw SocketException("Address already in use", SocketException::CONNECT);

   }
}

Socket::~Socket()
{
   if (is_valid())
    ::close(sockfd);
}

const Socket &Socket::operator<<(const string &outbuff) const
{
   if (::send (sockfd, outbuff.c_str(), outbuff.size(), 0) == -1)
    throw SocketException("Error while sending message", SocketException::SEND);

return *this; 
}

const Socket &Socket::operator<<(const int &intbuff) const
{
   string outbuff = IntToString(intbuff);

   if (::send (sockfd, outbuff.c_str(), outbuff.size(), 0) == -1)
    throw SocketException("Error while sending message", SocketException::SEND);

return *this;
}


const Socket &Socket::operator>>(string &inbuff) const
{
   char buf [MAXRECV+1];
   memset(buf, 0, MAXRECV + 1);

   int status = ::recv (sockfd, buf, MAXRECV, 0);

   if (status == -1)
    throw SocketException("Error while recieving from server", SocketException::RECV);
   else if ( status == 0 )
    throw SocketException("Remote server closed connection", SocketException::RECV);
   else
    inbuff = buf;

return *this;
}

Socket *eSock = NULL;

} // namespace eNetworks
