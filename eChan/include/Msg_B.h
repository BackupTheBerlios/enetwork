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

#ifndef ELECTRONIC_NETWORKS__MSG_B_H
#define ELECTRONIC_NETWORKS__MSG_B_H

#include <string>

#include "Msg.h"

namespace eNetworks
{

// foward declaration
struct Channel;
// -------------------------------------------------------------------------------
//                    B Token. (A server introducing a channel)
// -------------------------------------------------------------------------------
class Msg_B : public Msg
{
   public:
        Msg_B(const std::string &aCommand, const std::string &aToken) : Msg(aCommand, aToken) {}

        virtual ~Msg_B() {}
        virtual void Parser();

   protected:
   	void ParseUsers(Channel *aChannelPtr, const std::string &UsersParameters);
   	void ParseBans(Channel *aChannelPtr, const std::string &BansParameters);

};

// -------------------------------------------------------------------------------
//                    BURST Token. (Extra channel clients and bans)
// -------------------------------------------------------------------------------

class Msg_Burst : public Msg_B
{
   public:
   	Msg_Burst(const std::string &aCommand, const std::string &aToken) : Msg_B(aCommand, aToken) {}

   	virtual ~Msg_Burst() {}
   	virtual void Parser();
};


} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__MSG_B_H
