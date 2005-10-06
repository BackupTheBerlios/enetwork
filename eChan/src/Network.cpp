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

#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

#include "Client.h"
#include "Network.h"
#include "Server.h"
#include "Channel.h"
#include "ConfigParser.h"
#include "tools.h"
#include "Socket.h"
#include "SocketException.h"
#include "debug.h"

using std::map;
using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

Network::Network(ConfigParser& theConfigParser) : Servers(), ClientNumerics(), ClientNickNames(), Channels() 
{

   LocalServer = new Server(theConfigParser.GetConfiguration("NUMERIC"), theConfigParser.GetConfiguration("SERVERNAME"), "", 
   	   	   	    theConfigParser.GetConfiguration("SERVERINFO"), time(0), time(0), 1, 's');

   if (LocalServer == NULL)
   {
   	cout << "Could not create server: " << theConfigParser.GetConfiguration("SERVERNAME") << endl;
   	exit(0);
   }

   LocalClient = new Client(theConfigParser.GetConfiguration("NUMERIC")+"AAC", theConfigParser.GetConfiguration("NICK"), "", 
   	   	   	    theConfigParser.GetConfiguration("USERNAME"), theConfigParser.GetConfiguration("HOSTNAME"),
                            "DAqAoB", "idk", theConfigParser.GetConfiguration("CLIENTINFO"), time(0), 1);

   if (LocalClient == NULL)
   {
   	cout << "Could Not add client " << theConfigParser.GetConfiguration("NICK") << endl;
        exit(0);
   }

   try
   {
   	eSock = new Socket(theConfigParser.GetConfiguration("UPLINK"), StringToInt(theConfigParser.GetConfiguration("PORT")));
   }
   catch (SocketException &sockerr)
   {
   	sockerr.log();
   	sockerr.fix();
   }
}



// -----------------------------
//  Servers Management members.
// -----------------------------

bool Network::AddServer(const std::string &aNumeric, const std::string &aName, const std::string &aUpLinkNumeric,
               const std::string &aDescription, const time_t &aStartTime, const time_t &aLinkTime,
               const unsigned int &aHopCount, const char &aFlag)
{
   // Check we don't get bogus entries. If we do return false.
   if (aUpLinkNumeric.length() > 2 || aUpLinkNumeric.find(" ") != string::npos ||
       aName.find(" ") != string::npos || aNumeric.length() > 2 ||
       aNumeric.find(" ") != string::npos || aHopCount == 0 ||
       FindServerByNumeric(aNumeric) != NULL)
   {
        return false;
   }

   // Allocate a new server on the heap.
   Server *NewServer = new Server(aNumeric, aName, aUpLinkNumeric, aDescription, aStartTime, aLinkTime, aHopCount, aFlag);

   // If server could not be allocated on the heap OR there was a problem inserting the server in the
   // Server map table, return false.
   if (NewServer == NULL || Servers.insert(ServerMapType::value_type(aNumeric, NewServer)).second == false)
   {
   	delete NewServer;
   	return false;
   }

   // Add this server to the DownLinks list of its uplink.
   FindServerByNumeric(aUpLinkNumeric)->ServerDownLinks.push_back(aNumeric);

// everything went well.
return true;
}

bool Network::DelServerByNumeric(const std::string &aNumeric)
{
   // try to find a server with numeric: aNumeric.
   ServerMapType::iterator ServerIter = Servers.find(aNumeric);

   // if none was found return false.
   if (ServerIter == Servers.end())
   {
   	return false;
   }

   // Delete clients that are in this server.
   for (Server::ServerClientsIterator i = ServerIter->second->ServerClients.begin(); 
        i != ServerIter->second->ServerClients.end(); i++)
   {
   	DelClientByNumeric(i->second->Numeric);
   }

/*
   // Delete servers that are linked to this server.
   for(ServerMapType::iterator i = Servers.begin(); i != Servers.end(); i++)
   {
   	cout << "Iterating through: " << i->second->Name << ". That has UpLink: " << i->second->UpLinkNumeric << endl;
   	if (i->second->UpLinkNumeric == ServerIter->first)
   	{
   	   cout << "Deleting Server " << i->second->Name << endl;
   	   if (!DelServerByNumeric(i->second->Numeric))
   	   {
   	   	debug << "Could not delete server within server" << endb;
   	   	exit(0);
   	   }
   	}
   } 
*/

   // Delete servers that are linked to this server.
   for (Server::ServerDownLinksIterator i = ServerIter->second->ServerDownLinks.begin(); i != ServerIter->second->ServerDownLinks.end(); i++)
   {
   	DelServerByNumeric(*i);
   }

   // delete the Server from memory.
   delete ServerIter->second;
   // then finally remove the server from the Server Map table.
   Servers.erase(ServerIter); 

   cout << "Server Count: " << Servers.size() << endl;

return true;
}

bool Network::DelServerByName(const std::string &aName)
{
   // Search server by server name then call DelServerByNumeric.
   // DelServerByNumeric is faster than this.
   for (ServerMapType::iterator i = Servers.begin(); i != Servers.end(); i++)
   {
   	if (i->second->Name == aName)
   	{
   	   DelServerByNumeric(i->second->Numeric);
   	   return true;
   	}
   }

return false;
}

Server *Network::FindServerByNumeric(const std::string &aNumeric)
{
   ServerMapType::iterator ServerIter = Servers.find(aNumeric);

   if (ServerIter == Servers.end())
   {
   	return NULL;
   }
   // else
   return ServerIter->second;
}

Server *Network::FindServerByName(const std::string &aName)
{
   // Search server by server to see if the server name matches.
   // NOTE: FindServerByNumeric is faster than this.
   for (ServerMapType::iterator i = Servers.begin(); i != Servers.end(); i++)
   {
   	if (i->second->Name == aName)
   	{
   	   return i->second;
   	}
   }

return NULL;
}

// -----------------------------
//  Clients Management members.
// -----------------------------

bool Network::AddClient(const std::string &aNumeric, const std::string &aNickName, const std::string &aAccount,
                        const std::string &aUserName, const std::string &aHostName, const std::string &aB64IP,
                        const std::string &aModes, const std::string &aUserInfo, const time_t &aTimeStamp,
                        const unsigned int &aHopCount)
{

   cout << "Numeric: " << aNumeric << " NickName: " << aNickName << " Account: " << aAccount <<
           " UserName: " << aUserName << " HostName: " << aHostName << " B64IP: " << aB64IP << " Modes: " << aModes
           << " TimeStamp: " << aTimeStamp << " HopCount: " << aHopCount << endl << "UserInfo: " << aUserInfo << endl;

   // Check we don't get bogus entries.
   if (aNickName.length() == 0 || aNickName.find(" ") != string::npos || aNumeric.length() != 5 ||
       aUserName.length() == 0 || aUserName.find(" ") != string::npos ||
       aHostName.length() == 0 || aHostName.find(" ") != string::npos || aB64IP.length() == 0 ||
       aB64IP.find(" ") != string::npos || FindServerByNumeric(aNumeric.substr(0,2)) == NULL ||
       aTimeStamp < FindServerByNumeric(aNumeric.substr(0,2))->StartTime ||
       FindClientByNickName(aNickName) != NULL || FindClientByNumeric(aNumeric) != NULL)
   {
        return false;
   }


   // create the new client. Allocate memory for it on the heap.
   Client *NewClient = new Client(aNumeric, aNickName, aAccount, aUserName, aHostName, aB64IP, aModes, aUserInfo, 
                                  aTimeStamp, aHopCount);


   // if we couldn't allocate the new client or we can't insert the new user to the client map table, return false.
   if (NewClient == NULL || !ClientNumerics.insert(ClientNumericsMapType::value_type(aNumeric, NewClient)).second)
   {
   	delete NewClient;
   	return false;
   }

   // try to insert the new client to the user map table associated by its nicknames, if we can't delete the client,
   // remove the client from the user map table associated by nicknames and return false.
   if(ClientNickNames.insert(ClientNickNamesMapType::value_type(aNickName, NewClient)).second == false)
   {
   	ClientNumerics.erase(aNumeric);
   	delete NewClient;
   	return false;
   }

   // Make this user dependent of its server.
   FindServerByNumeric(aNumeric.substr(0,2))->ServerClients.insert(Server::ServerClientsType::value_type(aNumeric.substr(2),
                                                                                                         NewClient));

return true;
}

bool Network::DelClientByNickName(const std::string &aNickName)
{
   // Try to find the client.
   ClientNickNamesMapType::iterator ClientIter = ClientNickNames.find(aNickName);

   // return false if client with this nicname doesn't exist.
   if (ClientIter == ClientNickNames.end())
   {
   	return false;
   }

   // try to remove from the table associated by numerics first.
   if (ClientNumerics.erase(ClientIter->second->Numeric) != 1)
   {
   	return false;
   }

   // then remove the client from the client table in the server this client is dependant on.
   FindServerByNumeric(ClientIter->second->Numeric.substr(0,2))->ServerClients.erase(ClientIter->second->Numeric.substr(2));

   // remove this client from every channel it is on.
   for (Client::ChannelMapType::iterator i = ClientIter->second->ChannelMap.begin(); 
        i != ClientIter->second->ChannelMap.end(); i++)
   {
   	i->second->DelChannelClient(ClientIter->second); 
   }

   // finally release memory allocated and remove from table associated by nicknames.
   delete ClientIter->second;
   ClientNickNames.erase(ClientIter);

return true;
}

bool Network::DelClientByNumeric(const std::string &aNumeric)
{
   // try to find the client.
   ClientNumericsMapType::iterator ClientIter = ClientNumerics.find(aNumeric);

   // if client doesn't exist return false.
   if (ClientIter == ClientNumerics.end())
   {
        return false;
   }

   // try to erase the client from the client table associated by nicknames.
   if (ClientNickNames.erase(ClientIter->second->NickName) != 1)
   {
        return false;
   }

   // then remove the client from the client table in the server this client is dependant on.
   FindServerByNumeric(aNumeric.substr(0,2))->ServerClients.erase(aNumeric.substr(2));

   // remove this client from ever channel it is on.
   for (Client::ChannelMapType::iterator i = ClientIter->second->ChannelMap.begin();
        i != ClientIter->second->ChannelMap.end(); i++)
   {
   	i->second->DelChannelClient(ClientIter->second);
   }

   // finally release memory allocated and remove from table associated by numerics.
   delete ClientIter->second;
   ClientNumerics.erase(ClientIter);

return true;
}

Client *Network::FindClientByNickName(const std::string &aNickName)
{

   ClientNickNamesMapType::iterator ClientIter = ClientNickNames.find(aNickName);

   if (ClientIter == ClientNickNames.end())
   {
   	return NULL;
   }
   // else
   return ClientIter->second;
}

Client *Network::FindClientByNumeric(const std::string &aNumeric)
{
   ClientNumericsMapType::iterator ClientIter = ClientNumerics.find(aNumeric);

   if (ClientIter == ClientNumerics.end())
   {
   	return NULL;
   }
   // else
   return ClientIter->second;
}


// -----------------------------
//  Channels Management members.
// -----------------------------

bool Network::AddChannel (const std::string &aName, const time_t &aTimeStamp, const std::string &aTopic, 
   	   	   	 const std::string &aModes, const std::string &aKey, const unsigned int &aLimit)
{
   // check we don't get bogus entries.
   if (aName.length() == 0 || (aName[0] != '#' && aName[0] != '+'))
    return false;

   // allocate memory for this channel.
   Channel *NewChannel = new Channel(aName, aTopic, aModes, aKey, aLimit, aTimeStamp);

   // return false if NewChannel is null (which means no memory could be allocated) or if for some reason
   // we can't add it to the channel table.
   if (NewChannel == NULL || !Channels.insert(ChannelMapType::value_type(aName, NewChannel)).second)
   {
   	delete NewChannel;
   	return false;
   }

return true;
}

bool Network::DelChannel(const std::string &aName)
{
   // return true if we deleted the channel
   if (Channels.erase(aName) == 1)
    return true;
   // else return false.
    return false;
}

Channel *Network::FindChannel(const std::string &aName)
{
   ChannelMapType::iterator ChannelIter = Channels.find(aName);  

   if (ChannelIter == Channels.end())
    return NULL;
   // else
   return ChannelIter->second;
}

Network* eNetwork;

} // namespace eNetwork
