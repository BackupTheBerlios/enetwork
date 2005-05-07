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

#include <list>
#include <string>

#include "Network.h"
#include "Client.h"
#include "Channel.h"

using std::string;

namespace eNetworks
{

// Add a ChannelClient to the ChannelClientList. return false if aClientPtr
// is NULL or if modes are invalid. (different to 'o' or 'v')
bool Channel::AddChannelClient(Client *aClientPtr, const string &aModes)
{
   // Check we don't get bogus entries.
   if (aClientPtr == NULL || aModes.find(' ') != string::npos || IsChannelClient(aClientPtr->GetNumeric()))
    return false;

   // Only modes o and v are accepted.
   if (aModes.length() > 2)
    return false;

   // only channel modes o and v are accepted. Return false if any other is passed.
   for(unsigned int i = 0; i < aModes.length(); i++)
    if (aModes[i] != 'o' && aModes[i] != 'v')
     return false;

   // create the new channel client.
   ChannelClient *NewChannelClient = new ChannelClient(aClientPtr, aModes);

   // if we couldn't add the client to the client list the return false.
   if (!ChannelClientList.insert(ChannelClientListType::value_type(aClientPtr->GetNumeric(), NewChannelClient)).second) 
   {
   	return false;
   }

   // Add this channel to the channel list of this client.
   aClientPtr->AddChannel(this);

return true;
}

// Delete a ChannelClient from the ChannelClientList. return false if aClientIterator
// is invalid.
bool Channel::DelChannelClient(Client *aClientPtr)
{
   if (aClientPtr == NULL)
    return false;

   ChannelClientIterator ChannelClientIter = ChannelClientList.find(aClientPtr->GetNumeric()); 

   if (ChannelClientIter != ChannelClientList.end())
   {
   	aClientPtr->DelChannel(this); 
  	delete ChannelClientIter->second;
   	ChannelClientList.erase(ChannelClientIter);

   	// If that was the last User in this channel then delete the channel.
   	if (ChannelClientList.empty())
   	{
   	   eNetwork->DelChannel(this->GetName());
   	}
   	return true;
   }
 
return false;
}      

// Checks if the ClientIterator is in this Channel. return false if the ClientIterator is not
// in the client list or if the ClientIterator is not in the Channel. Otherwise return true.
bool Channel::IsChannelClient(Client *aClientPtr)
{
   if (aClientPtr == NULL)
    return false;

   if (ChannelClientList.find(aClientPtr->GetNumeric()) == ChannelClientList.end())
    return false;

return true;
}

bool Channel::IsChannelClient(const std::string &aNumeric)
{
   if (ChannelClientList.find(aNumeric) == ChannelClientList.end())
    return false;

return true;
}

ChannelClient *Channel::FindChannelClient(Client *aClientPtr)
{
   if (aClientPtr == NULL)
    return NULL;

   ChannelClientIterator ChannelClientIter = ChannelClientList.find(aClientPtr->GetNumeric());

   if (ChannelClientIter == ChannelClientList.end())
    return NULL;
   // else
    return ChannelClientIter->second;
}

ChannelClient *Channel::FindChannelClient(const std::string &aNumeric)
{
   ChannelClientIterator ChannelClientIter = ChannelClientList.find(aNumeric);
 
   if (ChannelClientIter == ChannelClientList.end())
    return NULL;
   // else
    return ChannelClientIter->second;
}

} // namespace eNetworks
