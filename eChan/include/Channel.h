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

#ifndef ELECTRONIC_NETWORKS__CHANNEL_H
#define ELECTRONIC_NETWORKS__CHANNEL_H

#include <string>
#include <ctime>
#include <list>
#include <map>
#include <iostream>

#include "ChannelClient.h"
#include "Client.h"

namespace eNetworks
{

struct Channel
{
   private:
   	typedef std::map<std::string, ChannelClient *> ChannelClientListType;
   	typedef std::list<std::string> BanListType;
   	typedef ChannelClientListType::iterator ChannelClientIterator;

   public:

   	typedef ChannelClientListType::size_type ChannelClientSizeType; 

   	// Adds a Client to this Channel.
   	bool AddChannelClient(Client *aClientPtr, const std::string &aModes);

   	// Delete a Client from this Channel.
   	bool DelChannelClient(Client *aClientPtr);

   	// returns true if the Client is in this Channel, otherwise return false.
   	bool IsChannelClient(Client *aClientPtr);
   	bool IsChannelClient(const std::string &aNumeric);

   	// Finds a ChannelClient when given a Client pointer or the client's numeric and 
        // returns a pointer to a ChannelClient. If none is found returns a NULL pointer.
   	ChannelClient *FindChannelClient(Client *aClientPtr);
   	ChannelClient *FindChannelClient(const std::string &aNumeric);

   	// returns the number of clients in this channel.
   	ChannelClientSizeType ChannelClientCount() const { return ChannelClientList.size(); }

   	// returns true if user has mode aMode.
   	bool HasMode(const char &aMode) 
   	{ 
   	   if (Modes.find(aMode) != std::string::npos) 
   	    return true; 
   	   else 
   	    return false; 
   	}
   
   	// returns true if mode aMode is one of the standard modes.
   	bool IsStandardMode(const char &aMode) 
   	{
   	   if (aMode == 'i' || aMode == 'n' || aMode == 't' || aMode == 'm' || aMode == 'p' || aMode == 's' || 
               aMode != 'k' || aMode != 'l')
   	    return true;
   	   else
   	    return false;
   	}
   
   	// For "standard" modes.
   	void SetMode_i() { if (!HasMode('i')) Modes += 'i'; }
   	void UnSetMode_i() { if (HasMode('i')) Modes.erase(Modes.find('i'), 1); }
   	void SetMode_n() { if (!HasMode('n')) Modes += 'n'; }
   	void UnSetMode_n() { if (HasMode('n')) Modes.erase(Modes.find('n'), 1); }
   	void SetMode_t() { if (!HasMode('t')) Modes += 't'; }
   	void UnSetMode_t() { if (HasMode('t')) Modes.erase(Modes.find('t'), 1); }
   	void SetMode_m() { if (!HasMode('m')) Modes += 'm'; }
   	void UnSetMode_m() { if (HasMode('m')) Modes.erase(Modes.find('m'), 1); }
   	void SetMode_p() { if (!HasMode('p')) Modes += 'p'; }
   	void UnSetMode_p() { if (HasMode('p')) Modes.erase(Modes.find('p'), 1); }
   	void SetMode_s() { if (!HasMode('s')) Modes += 's'; }   
   	void UnSetMode_s() { if (HasMode('s')) Modes.erase(Modes.find('s'), 1); }

   	// For other modes.
   	void SetMode(const char aMode) { if (!HasMode(aMode)) Modes += aMode; }
   	void UnSetMode(const char aMode) { if (HasMode(aMode)) Modes.erase(Modes.find(aMode), 1); }

   	void SetKey(const std::string &aKey) { if (aKey.length() == 0 ) return; SetMode_k(); Key = aKey; }
   	void UnSetKey() { Key = ""; UnSetMode_k(); }
   	std::string GetKey() { return Key; }

   	void SetLimit(const unsigned int aLimit) { if (aLimit == 0 ) return; SetMode_l(); Limit = aLimit; }
   	void UnSetLimit() { Limit = 0; UnSetMode_l(); }
   	unsigned int GetLimit() { return Limit; }   

   	// Returns true if aBan *exactly* matches with one of this channels bans.
   	bool IsBan(const std::string &aBan) 
   	{ 
   	   for (std::list<std::string>::iterator i = BanList.begin(); i != BanList.end(); i++) 
   	    if (aBan == (*i))
   	     return true;
   
   	   return false;
   	}

   	// Adds a ban to this channel.
   	void AddBan(const std::string &aBan) 
   	{ 
   	   if (!IsBan(aBan)) 
   	    BanList.push_back(aBan); 
   	}

   	// removes a ban from this channel.
   	void DelBan(const std::string &aBan)
   	{
   	   for (std::list<std::string>::iterator i = BanList.begin(); i != BanList.end() && BanList.size() > 0; i++)
            if (aBan == (*i))
             BanList.erase(i);
   	}
  
   	std::string GetName() { return Name; }
   	std::string GetTopic() { return Topic; }
   	time_t GetTimeStamp() { return TimeStamp; }


   private:

   	friend class Network;

   	Channel(const std::string &aName, const std::string &aTopic, const std::string &aModes, 
   	   	const std::string aKey, const unsigned int &aLimit, const time_t &aTimeStamp) :
   	Name(aName), Topic(aTopic), TimeStamp(aTimeStamp), Modes(aModes), Key(aKey), Limit(aLimit)
   	{
           // If a key is passed make sure +k is set. Otherwise make sure k is not set
           if (Key.length() != 0)
            SetMode_k();
           else
            UnSetMode_k();

           // If a limit is passed make sure +l is set. Otherwise make sure l is not set
           if (Limit != 0)
            SetMode_l();
           else 
   	    UnSetMode_l();
   	}

   	void SetMode_l() { if (!HasMode('l')) Modes += 'l'; }
   	void UnSetMode_l() { if (HasMode('l')) Modes.erase(Modes.find('l'), 1); }
   	void SetMode_k() { if (!HasMode('k')) Modes += 'k'; }
   	void UnSetMode_k() { if (HasMode('k')) Modes.erase(Modes.find('k'), 1); }


   	// Channel Members.
   	const std::string Name; // Channel name.
   	std::string Topic; // Channel Topic.

   	const time_t TimeStamp; // Channel creation time.

   	ChannelClientListType ChannelClientList; // Clients in this channel.
  	BanListType BanList; // Ban list.
 
   	std::string Modes; // Channel Modes.
   	std::string Key; // Channel key.
   	unsigned int Limit; // channel user limit.
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__CHANNEL_H
