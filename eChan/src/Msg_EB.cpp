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
#include <iostream>

#include "debug.h"
#include "Msg_EB.h"
#include "Socket.h"
#include "P10Tokens.h"
#include "Server.h"

using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

void Msg_EB::Parser()
{
   if (ServerSrc == NULL)
   {
   	debug << "ServerSrc is NULL in Msg_EB::Parser()." << endb;
   	exit(0);
   }

   (*eSock) << LocalServer->GetNumeric() << " " << Tokens::END_OF_ACK << "\r\n";
   cout << "[OUT]: " <<  LocalServer->GetNumeric() << " " << Tokens::END_OF_ACK << endl;

/*
   (*eSock) << LocalServer->GetNumeric() << " G !1071288273.976939 test.vodanet.org 1071288273.976939\r\n";
   cout << "[OUT]: " << LocalServer->GetNumeric() << " G !1071288273.976939 test.vodanet.org 1071288273.976939" << endl;
*/

}

} // namespace eNetworks
