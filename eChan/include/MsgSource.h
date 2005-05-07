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

#ifndef ELECTRONIC_NETWORKS__MSGSOURCE_H
#define ELECTRONIC_NETWORKS__MSGSOURCE_H

#include <string>
#include <cstdlib>

#include "Client.h"
#include "Server.h"

using std::string;

namespace eNetworks
{

class MsgSource 
{
   public:
   	MsgSource() : aClient(NULL), aServer(NULL) {}
   	MsgSource(Client* _aClient) : aClient(_aClient), aServer(NULL) { if (NULL == aClient) exit(0); }
   	MsgSource(Server* _aServer) : aClient(NULL), aServer(_aServer) { if (NULL == aServer) exit(0); } 

   	bool IsClient() const { if (NULL != aClient) return true; else return false; }
   	bool IsServer() const { if (NULL != aServer) return true; else return false; }
   	bool IsSourceless() const { if (NULL == aClient && NULL == aServer) return true; else return false; }

   	string GetNumeric() const { if (IsServer()) return aServer->GetNumeric(); else return aClient->GetNumeric(); }
   	string GetName() const { if (IsServer()) return aServer->GetName(); else return aClient->GetNickName(); }

   private:
   	Client* aClient;
   	Server* aServer;
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__MSGSOURCE_H
