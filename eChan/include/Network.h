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

#ifndef ELECTRONIC_NETWORKS__NETWORK_H
#define ELECTRONIC_NETWORKS__NETWORK_H

#include <map>
#include <string>
#include <cstring>

#include "tools.h"

namespace eNetworks
{

// foward declaration
struct Client;
struct Channel;
struct Server;

class Network
{
   private:
   	typedef std::map<std::string, Server *, noCaseCompare> ServerMapType;
   	typedef std::map<std::string, Client *> ClientNumericsMapType;
   	typedef std::map<std::string, Client *, noCaseCompare> ClientNickNamesMapType;
   	typedef std::map<std::string, Channel *, noCaseCompare> ChannelMapType;

   public:

   	Network() : Servers(), ClientNumerics(), ClientNickNames(), Channels() {}

   // ---------------------
   //  Servers Management.
   // ---------------------
   	// Type returned on ServerCount()
   	typedef ServerMapType::size_type ServerSizeType;

   	// Add a Server to the Server table. returns false of any of the arguments is invalid.
   	bool AddServer(const std::string &aNumeric, const std::string &aName, const std::string &aUpLinkNumeric,
                       const std::string &aDescription, const time_t &aStartTime, const time_t &aLinkTime,
                       const unsigned int &aHopCount, const char &Flag);

   	// Removes a server from the server table when given a server name. 
        // returns false when the server doesn't exist
   	bool DelServerByName(const std::string &aName);

        // Removes a server from the server table when given a server numeric.
        // returns false when the server doesn't exist
   	bool DelServerByNumeric(const std::string &aNumeric);

   	// Finds a server when give the name of the server.
   	// returns a pointer to the server if the server exists, 
   	// otherwise returns NULL
   	Server *FindServerByName(const std::string &aName);

   	// Finds a server when give the numeric of the server.
        // returns a pointer to the server if the server exists,
        // otherwise returns NULL
   	Server *FindServerByNumeric(const std::string &aName);

        // returns the number of servers in the server table.
   	ServerSizeType ServerCount() const { return Servers.size(); }   	

   // -----------------------------
   //  Clients Management Methods.
   // -----------------------------

   	typedef ClientNickNamesMapType::size_type ClientSizeType;

   	// Add a client to the client table.
   	bool AddClient(const std::string &aNumeric, const std::string &aNickName, const std::string &aAccount,
                       const std::string &aUserName, const std::string &aHostName, const std::string &aB64IP,
                       const std::string &aModes, const std::string &aUserInfo, const time_t &aTimeStamp,
                       const unsigned int &aHopCount);

   	// Deletes a Client from the Client table when given the NickName of the Client.
   	bool DelClientByNickName(const std::string &aNickName);
   	
   	// Deletes a Client from the Client table when give the Numeric of the Client.
   	bool DelClientByNumeric(const std::string &aNumeric);

   	// Finds a Client in the client table when given a NickName. 
   	// Returns a pointerto the client if a client is found.
   	// Otherwise returns a NULL pointer.
   	Client *FindClientByNickName(const std::string &aNickName);
  
   	// Finds a Client in the client table when given a Numeric.
   	// Returns a pointer to the client if a client is found.
   	// Otherwise returns a NULL pointer.
   	Client *FindClientByNumeric(const std::string &aNumeric);

   	// Returns the number of clients in the client table.
   	ClientSizeType ClientCount() const { return ClientNickNames.size(); }


   // -----------------------------
   //  Channels Management Methods.
   // -----------------------------

   	typedef ChannelMapType::size_type ChannelSizeType;

   	// Adds a channel to the network
   	bool AddChannel(const std::string &aName, const time_t &aTimeStamp, const std::string &aTopic = "", 
   	   	   	const std::string &aModes = "", const std::string &aKey = "", const unsigned int &aLimit = 0);

   	// Deletes a channel from the network
   	bool DelChannel(const std::string &aName);

   	// Finds a channel and return a pointer to the channel if the channel is found, 
        // otherwise returns a NULL pointer
   	Channel *FindChannel(const std::string &aName);
 
   	// returns the number of channels in the network
   	ChannelSizeType ChannelCount() const { return Channels.size(); }

   private:

   // Servers Management members.

        // Server table organized by Server Numerics.
   	ServerMapType Servers; 


   // Clients Management members.

   	// Clients table ordered by Client Numerics
   	ClientNumericsMapType ClientNumerics;

   	// Clients table ordered by Client NickNames
   	ClientNickNamesMapType ClientNickNames;  

   // Channels Management members.
   	
   	// Channels table ordered by Channel name
   	ChannelMapType Channels;

};


extern eNetworks::Network *eNetwork;
   	
} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__NETWORK_H
