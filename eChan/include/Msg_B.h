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

#ifndef ELECTRONIC_NETWORKS__MSG_B_H
#define ELECTRONIC_NETWORKS__MSG_B_H

#include <string>

#include "Msg.h"

namespace eNetworks
{

// foward declaration
struct Channel;
// -------------------------------------------------------------------------------
//                    N Token. (A server introducing a client)
// -------------------------------------------------------------------------------
class Msg_B : public Msg
{
   public:
        Msg_B(const std::string &aCommand, const std::string &aToken) : Msg(aCommand, aToken) {}

        virtual ~Msg_B() {}
        virtual void Parser();

   private:
   	void ParseUsers(Channel *aChannelPtr, const std::string &UsersParameters);
   	void ParseBans(Channel *aChannelPtr, const std::string &BansParameters);

}; // namespace eNetworks

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__MSG_B_H
