/*
 * eChan - Electronic Channel Services.
 * Copyright (C) 2003 Alan Alvarez.
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

#ifndef ELECTRONIC_NETWORKS__CHANNELCLIENT_H
#define ELECTRONIC_NETWORKS__CHANNELCLIENT_H

#include <string>

#include "Client.h"
#include "Channel.h"


namespace eNetworks
{
struct Client;

// This struct represents a Client member of a Channel. You cannot create instances of this struct,
// instead you have to use Channel::AddChannelClient.
struct ChannelClient
{

   public:

        // Adds a Mode to this channel user if the mode doesn't already exist.
        void AddMode(const char &aMode)
        {
           if (HasMode(aMode) || (aMode != 'o' && aMode != 'v'))
            return;

           Modes += aMode;
        }

        // Deletes a mode from this channel user if the mode already exists.
        void DelMode(const char &aMode)
        {
           if (!HasMode(aMode))
            return;
           else
            Modes.erase(Modes.find(aMode), 1);
        }

        // returns true if the aMode is in Modes. Otherwise returns false.
        bool HasMode(const char &aMode) const
        {
           if (Modes.find(aMode) == std::string::npos)
            return false;
           else
            return true;
        }

   private:
        // Make Channel friend of this struct so that it can make instances of this struct.
        friend class Channel;

        // Make consturctor private so that users can't create instances of this class.
        ChannelClient(Client *aClientPtr, const std::string &aModes = "") :
        ClientPtr(aClientPtr), Modes(aModes) {}

        Client *ClientPtr; // The client this struc is representing.
        std::string Modes; // the channel modes for this user.
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__CHANNELCLIENT_H
