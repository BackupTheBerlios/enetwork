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

#ifndef ELECTRONIC_NETWORKS__MSG_N_H
#define ELECTRONIC_NETWORKS__MSG_N_H

#include <string>

#include "Msg.h"

namespace eNetworks
{

// -------------------------------------------------------------------------------
//                    N Token. (A server introducing a client)
// -------------------------------------------------------------------------------
class Msg_N : public Msg
{
   public:
        Msg_N(const std::string &aCommand, const std::string &aToken) : Msg(aCommand, aToken) {}

        virtual ~Msg_N() {}
        virtual void Parser();
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__MSG_N_H
