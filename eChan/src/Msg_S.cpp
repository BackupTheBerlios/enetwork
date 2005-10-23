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

#include <string>
#include <iostream>

#include "Network.h"
#include "Msg_S.h"
#include "debug.h"
#include "Server.h"

using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

// ========
//  Msg_S
// ========

void Msg_S::Parser()
{

   if (!Source.IsServer())
   {
        debug << "Protocol Violation. Token S with no source." << endb;
        exit(0);
   }

   if (Parameters.size() < 6 && Parameters.size() > 8)
   {
        debug << "Protocol Violation: Too Many Parameters in Msg_S::Parser()" << endb;
        exit(0);
   }

   string Name = Parameters[0];

   unsigned int HopCount;
   if (StringToInt(Parameters[1]) < 2)
   {
        debug << "Protocol Violation: Hop Count shouldn't be less than 2 in Msg_S::Parser()" << endb;
        exit(1);
   }
   else
    HopCount = StringToInt(Parameters[1]);

   time_t StartTime;
   if (!IsDigit(Parameters[2]))
   {
        debug << "Protocol Violation: StartTime should be only digit numbers in Msg_S::Parser()" << endb;
        exit(1);
   }
   else
    StartTime = StringToInt(Parameters[2]);

   time_t LinkTime;
   if (!IsDigit(Parameters[3]))
   {
        debug << "Protocol Violation: LinkTime should be only digit numbers in Msg_S::Parser()" << endb;
        exit(1);
   }
   else
    LinkTime = StringToInt(Parameters[3]);

   if (Parameters[4] != "P10" && Parameters[4] != "J10")
   {
        debug << "Protocol Violation: Protocol should be P10 in Msg_S::Parser()" << endb;
        exit(1);
   }

   string B64IP = Parameters[4];

   string Numeric = Parameters[5].substr(0,2);

   char Flag = '0';
   string Description;
   if (Parameters.size() == 8)
   {
        if (Parameters[6][0] == '+' && Parameters[6].size() > 1)
         Flag = Parameters[6][1];

        Description = Parameters[7];
   }
   else
    Description = Parameters[6];

   if (!Network::Interface.AddServer(Numeric, Name, Source.GetNumeric(), Description, StartTime, LinkTime, HopCount, Flag))
   {
        debug << "Could not add Server Name" << endb;
        exit(0);
   }
 
   debug << "Added Server Name: " << Name << " Numeric: " << Numeric << " StartTime: " << IntToString(StartTime) <<
           " LinkTime: " << IntToString(LinkTime) << " HopCount: " << IntToString(HopCount) << " Uplink: " <<
           Source.GetNumeric() << endb <<  "Description: " << Description << endb;

}

} // namespace eNetworks
