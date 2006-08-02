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

#ifndef ELECTRONIC_NETWORKS__MSGSOURCE_H
#define ELECTRONIC_NETWORKS__MSGSOURCE_H

#include <string>
#include <cstdlib>

#include "Client.h"
#include "Server.h"

using std::string;

namespace eNetworks
{

// This class represents the source of an IRC message.
// The interface tries to hide whether the message came
// from an user or a server. But if needed this information
// can be provided too.
class MsgSource 
{
   public:
   	// Creates a sourceless message.
   	MsgSource() : aClient(NULL), aServer(NULL) {}

   	// Sets _aClient as the source.
   	MsgSource(Client* _aClient) : aClient(_aClient), aServer(NULL) { if (NULL == aClient) exit(0); }

   	// Sets _aServer as the source.
   	MsgSource(Server* _aServer) : aClient(NULL), aServer(_aServer) { if (NULL == aServer) exit(0); } 

   	// returns whether the source is a Client or not.
   	bool IsClient() const { if (NULL != aClient) return true; else return false; }

   	// returns wheter the source is a server or not.
   	bool IsServer() const { if (NULL != aServer) return true; else return false; }

   	// returns wheter there is a set source or not.
   	bool IsSourceless() const { if (NULL == aClient && NULL == aServer) return true; else return false; }

   	// returns the numeric of the source.
   	string GetNumeric() const { return IsServer() ? aServer->GetNumeric() : aClient->GetNumeric(); }

   	// returns the Name of the Source.
   	string GetName() const { return IsServer() ? aServer->GetName() : aClient->GetNickName(); }

   	// returns a pointer to the Client Source.
   	Client* GetClient() const { return aClient; }

   	// returns a pointer to the Server Source.
   	Server* GetServer() const { return aServer; }

   private:
   	Client* aClient;
   	Server* aServer;
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__MSGSOURCE_H
