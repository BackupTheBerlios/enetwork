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

#ifndef ELECTRONIC_NETWORKS__SERVER_H
#define ELECTRONIC_NETWORKS__SERVER_H

#include <string>
#include <map>

#include "Client.h"

namespace eNetworks
{

// foward declaration
struct Client;

struct Server
{
   friend void CreateLocals();
   friend class Network;   

   public:
   	// Public Accessors.
   	std::string GetName() const { return Name; }
   	std::string GetNumeric() const { return Numeric; }
   	std::string GetUpLink() const { return UpLinkNumeric; }
   	std::string GetDescription() const { return Description; }
   	time_t GetStartTime() const { return StartTime; }
   	time_t GetLinkTime() const { return LinkTime; }
   	unsigned int GetHopCount() const { return HopCount; }
   	char GetFlag() const { return Flag; }

   private: // only NumericServers and NameServers can touch this struct.
   	// Client numeric represented by CCC in contrast to SSCCC.
   	typedef std::map<std::string, Client *> ServerClientsType;
   	typedef ServerClientsType::iterator ServerClientsIterator;

   	~Server()
   	{}

   	const std::string Numeric;
   	const std::string Name;
        std::string UpLinkNumeric;
        const std::string Description;

        const time_t StartTime;
        time_t LinkTime;

        const unsigned int HopCount;

        // h = HUB.
        // s = Services.
        // 0 = Normal Server.
   	const char Flag;

   	ServerClientsType ServerClients;
 
   	Server(const std::string &aNumeric, const std::string &aName, const std::string &aUpLinkNumeric, 
               const std::string &aDescription, const time_t &aStartTime, const time_t &aLinkTime, 
               const unsigned int &aHopCount, const char &aFlag) :
     	Numeric(aNumeric), Name(aName), UpLinkNumeric(aUpLinkNumeric), Description(aDescription),
        StartTime(aStartTime), LinkTime(aLinkTime), HopCount(aHopCount), Flag(aFlag), ServerClients()
     	{}

};

extern Server *LocalServer;

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__SERVER_H
