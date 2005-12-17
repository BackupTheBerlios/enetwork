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

#ifndef WIN32
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#else
#include <winsock.h>
#endif

#include <string>

#include "tools.h"
#include "SocketException.h"
#include "Socket.h"

using std::string;

namespace eNetworks
{

void Socket::connect(const string &host, const int& port)
{
   ::memset(&m_addr, 0, sizeof(m_addr));

   sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
   // Set as nonblocking.
#ifdef WIN32
   unsigned long blocking = 0; // disable blocking
   ioctlsocket(sockfd, FIONBIO, &blocking);
#else
   fcntl(sockfd, F_SETFL, O_NONBLOCK);
#endif

   if (!is_valid())
    throw SocketException("Could not create socket", SocketException::SOCKET);

   // TIME_WAIT - argh
   int on = 1;
   if (::setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*) &on, sizeof(on)) == -1)
    throw SocketException("Could not re-use socket address", SocketException::SETSOCKOPT);

   m_addr.sin_family = AF_INET;
   m_addr.sin_port = htons(port);
   m_addr.sin_addr.s_addr = inet_addr(host.c_str());

   // ::inet_pton(AF_INET, host.c_str(), &m_addr.sin_addr);

   if (::connect (sockfd, (sockaddr *) &m_addr, sizeof(m_addr)) == -1)
   {
#ifdef WIN32
	   switch(WSAGetLastError())
	   {
	   
	   case WSAEISCONN:
		   throw SocketException("This socket is already connected", SocketException::CONNECT);
		   break;

	   case WSAECONNREFUSED:
		   throw SocketException("Connection refused", SocketException::CONNECT);
		   break;

	   case WSAETIMEDOUT:
		   throw SocketException("Connection timed out", SocketException::CONNECT);
		   break;

	   case WSAENETUNREACH:
		   throw SocketException("Network is unreachable", SocketException::CONNECT);
		   break;

	   case WSAEADDRINUSE:
		   throw SocketException("Address already in use", SocketException::CONNECT);
		   break;
	   }
#else
   	switch (errno)
   	{
   	   case EISCONN:
   	   	throw SocketException("This socket is already connected", SocketException::CONNECT);
   	   	break;

   	   case ECONNREFUSED:
   	   	throw SocketException("Connection refused", SocketException::CONNECT);
   	   	break;

   	   case ETIMEDOUT:
   	   	throw SocketException("Connection timed out", SocketException::CONNECT);
   	   	break;

   	   case ENETUNREACH:
   	   	throw SocketException("Network is unreachable", SocketException::CONNECT);
   	   	break;

   	   case EADDRINUSE:
   	   	throw SocketException("Address already in use", SocketException::CONNECT);
   	   	break;
   	}
#endif
   }
}

std::string Socket::recv() const
{
   char buf [MAXRECV+1];
   memset(buf, 0, MAXRECV + 1);

//   int status = ::recv(sockfd, buf, MAXRECV, 0);

   switch (::recv(sockfd, buf, MAXRECV, 0))
   {
   	case -1:
   	   throw SocketException("Error while recieving from server", SocketException::RECV);
   	   *buf = '\0';
   	   break;

   	case 0:
   	   throw SocketException("Remote server closed connection", SocketException::RECV);
   	   *buf = '\0';
   	   break;
   }

   return string(buf);
}

Socket Socket::eSock = Socket();

} // namespace eNetworks
