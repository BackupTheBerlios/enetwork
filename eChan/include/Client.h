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

#ifndef ELECTRONIC_NETWORKS__CLIENT_H
#define ELECTRONIC_NETWORKS__CLIENT_H

#include <string>
#include <map>

#include "tools.h"

namespace eNetworks
{

// foward declaration.
struct Channel;

struct Client
{

   public:
   	// Clear all channels from this user.
   	void ClearChannels();

   	// Add a mode to this user.
   	void AddMode(const char &aMode) 
   	{ 
   	   // if the mode doesn't exist then add it, Otherwise don't do anything.
   	   if (!HasMode(aMode)) 
   	   {
   	   	Modes += aMode; 
   	   } 
   	}
  
   	// delete a mode from this user
   	void DelMode(const char &aMode)
   	{
   	   // If mode exists, remove it.
   	   if (HasMode(aMode))
   	   {
   	      Modes.erase(Modes.find(aMode), 1); // Remove Character from string.
   	   }
   	}

   	bool HasMode(const char aMode) const
   	{ 
   	   if (Modes.find(aMode) == std::string::npos) 
   	   {
   	   	return false; 
   	   }
   	   else 
   	   {
   	   	return true;
   	   }
   	}

   	bool IsOper() const
   	{
   	   return HasMode('o');
   	}

   	void ChangeNickName (const std::string &aNickName) { NickName = aNickName; }
   	void ChangeTimeStamp (const time_t &aTimeStamp) { TimeStamp = aTimeStamp; }

   	std::string GetNumeric() const { return Numeric; }
   	std::string GetNickName() { return NickName; }
   	std::string GetAccount() const { return Account; }
   	std::string GetUserName() const { return UserName; }
   	std::string GetHostName() const { return HostName; }
   	std::string GetB64IP() const { return B64IP; }
   	std::string GetUserInfo() const { return UserInfo; }
   	time_t GetTimeStamp() const { return TimeStamp; }
   	unsigned int GetHopCount() const { return HopCount; } 

   private:

   	friend class Network;
   	friend class Channel;

   	// type for Channel List.
   	typedef std::map<std::string, Channel *, noCaseCompare> ChannelMapType;


        // Make constructor private so that only Network class can create new instances.
        Client::Client(const std::string &aNumeric, const std::string &aNickName, const std::string &aAccount,
                       const std::string &aUserName, const std::string &aHostName, const std::string &aB64IP,
                       const std::string &aModes, const std::string &aUserInfo, const time_t &aTimeStamp,
                       const unsigned int &aHopCount) :
        Numeric(aNumeric), NickName(aNickName), Account(aAccount), UserName(aUserName), HostName(aHostName),
        B64IP(aB64IP), UserInfo(aUserInfo), TimeStamp(aTimeStamp), HopCount(aHopCount), Modes(aModes), ChannelMap()
        {}

   	// Add a channel to this user's Channel list.
   	// NOTE: This function should only be called from Channel::AddChannelClient
   	bool AddChannel(Channel *aChannelPtr); 

   	// Delete a channel from this user's channe list.
   	// NOTE: This function should only be called from Channel::DelChannelClient
   	bool DelChannel(Channel *aChannelPtr);

   	const std::string Numeric; // Server+Client. 5 digits
   	std::string NickName; // This user's nickname
   	std::string Account; // This user's services account
   	std::string UserName; // this user's username
   	std::string HostName; // this user's hostname
   	const std::string B64IP; // Base-64 IP
   	const std::string UserInfo; // this user's info

   	time_t TimeStamp; // this user's timestamp

   	const unsigned int HopCount; // this user's hopcount

        std::string Modes; // this user's modes.
   	
   	ChannelMapType ChannelMap; // Channels this user's on.

};

// This is the local client.
extern Client *LocalClient;

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__CLIENT_H
