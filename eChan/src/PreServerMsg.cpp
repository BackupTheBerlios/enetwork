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

#include <ctime>
#include <string>
#include <iostream>

#include "PreServerMsg.h"
#include "Network.h"
#include "Server.h"
#include "debug.h"

using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

// ==============
//  PreServerMsg
// ==============

void PreServerMsg::Parser()
{
   if (Parameters.size() < 6 && Parameters.size() > 8)
   {
        debug << "Protocol Violation: Too Many Parameters in PreServerMsg::Parser()" << endb;
        exit(1);
   }

   string Name = Parameters[0];

   unsigned int HopCount;
   if (Parameters[1] != "1")
   {
        debug << "Protocol Violation: Hop Count should be 1 in PreServerMsg::Parser()" << endb;
        exit(1);
   }
   else
    HopCount = StringToInt(Parameters[1]);

  time_t StartTime;
   if (!IsDigit(Parameters[2]))
   {
   	debug << "Protocol Violation: StartTime should be only digit numbers in PreServerMsg::Parser()" << endb;
   	exit(1);
   }
   else
    StartTime = StringToInt(Parameters[2]);


   time_t LinkTime;
   if (!IsDigit(Parameters[3]))
   {
        debug << "Protocol Violation: LinkTime should be only digit numbers in PreServerMsg::Parser()" << endb;
        exit(1);
   }
   else
    LinkTime = StringToInt(Parameters[3]);

   if (Parameters[4] != "J10")
   {
        debug << "Protocol Violation: Protocol should be J10 at link time in PreServerMsg::Parser()" << endb;
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

   if (!eNetwork->AddServer(Numeric, Name, LocalServer->GetNumeric(), Description, StartTime, LinkTime, HopCount, Flag))
   {
        debug << "Could not add Server Name" << endb;
        exit(0);
   }

   /*
   cout << "Added Server Name: " << Name << " Numeric: " << Numeric << " StartTime: " << StartTime <<
           " LinkTime: " << LinkTime << " HopCount: " << HopCount << " Flag: " << Flag << endl <<
           "Description: " << Description << endl;
   */
}

} // namespace eNetworks
