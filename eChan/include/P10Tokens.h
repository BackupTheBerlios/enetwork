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

#ifndef ELECTRONIC_NETWORKS__P10TOKENS_H
#define ELECTRONIC_NETWORKS__P10TOKENS_H

#include <string>

namespace eNetworks
{

// Tokens sent from irc servers according to the P10 protocol.
namespace Tokens
{
   const std::string    SERVER             =  "S";
   const std::string    PASS               =  "PASS";
   const std::string    PRESERVER          =  "SERVER";
   const std::string    ERROR              =  "ERROR";
   const std::string    NICK               =  "N";
   const std::string    B                  =  "B";
   const std::string    BURST              =  "BURST";
   const std::string    JOIN               =  "J";
   const std::string    PART               =  "L";
   const std::string    PING               =  "G";
   const std::string    PONG               =  "Z";
   const std::string    TOPIC              =  "T";
   const std::string    END_OF_BURST       =  "EB";
   const std::string    END_OF_ACK         =  "EA";
   const std::string    ACCOUNT            =  "AC";
}

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__P10TOKENS_H
