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

#include "Client.h"
#include "tools.h"
#include "Msg_N.h"
#include "Network.h"
#include "debug.h"

using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

// ========
//  Msg_N
// ========

void Msg_N::Parser()
{

   // User Changing NickName
   if (Parameters.size() == 2)
   {

   	Client* ClientSrc = eNetwork->FindClientByNumeric(Source.GetNumeric());
        if (NULL == ClientSrc)
        {
           debug << "Protocol Violation: Token N with no Client source." << endb;
           exit(0);
        }

        cout << "Changing " << ClientSrc->GetNickName() << "'s nickname to ";
        ClientSrc->ChangeNickName(Parameters[0]);
        cout << ClientSrc->GetNickName() << endl;
        ClientSrc->ChangeTimeStamp(StringToInt(Parameters[1]));

        return;
   }

   

   if (Parameters.size() < 7 || Parameters.size() > 10)
   {
        debug << "Protocol Violation: error on number of arguments in Msg_N::Parser()" << endb;
        exit(0);
   }

   if (!Source.IsServer())
   {
        debug << "Protocol Violation: Token N with no Server source." << endb;
        exit(0);
   }

   string NickName = Parameters[0];

   unsigned int HopCount = StringToInt(Parameters[1]);

   if (HopCount < 1)
   {
        debug << "Protocol violation: HopCount cannot be less than 1 in Msg_S::parser()" << endb;
        exit(0);
   }

   time_t TimeStamp;
   if (!IsDigit(Parameters[2]))
   {
        debug << "TimeStamp can only have digit numbers in function Msg_S::parser()" << endb;
        exit(0);
   }
   else
    TimeStamp = StringToInt(Parameters[2]);

   string UserName = Parameters[3];
   string HostName = Parameters[4];

   string Modes = "";
   string Account = "";
   string B64IP = "";
   string Numeric = "";
   string UserInfo = "";

   if (Parameters[5][0] == '+')
   {
        Modes = Parameters[5].substr(1);
        if (Modes.find("r") != string::npos)
        {
           Account = Parameters[6];
           B64IP = Parameters[7];
           Numeric = Parameters[8];
           if (Parameters.size() == 10)
            UserInfo = Parameters[9];
        }
        else
   	{

           B64IP = Parameters[6];
           Numeric = Parameters[7];
           if (Parameters.size() == 9)
            UserInfo = Parameters[8];
   	}
   } 
   else
   {
        B64IP = Parameters[5];
        Numeric = Parameters[6];
        if (Parameters.size() == 8)
         UserInfo = Parameters[7];
   }

   if (!eNetwork->AddClient(Numeric, NickName, Account, UserName, HostName, B64IP, Modes, UserInfo, TimeStamp, HopCount))
   {

/*   	
   	cout << "Numeric: " << Numeric << " NickName: " << NickName << " Account: " << Account <<
                " UserName: " << UserName << " HostName: " << HostName << " B64IP: " << B64IP << " Modes: " << Modes
                << " TimeStamp: " << TimeStamp << " HopCount: " << HopCount << endl << "UserInfo: " << UserInfo << endl;
*/

        debug << "Could not add client " << NickName << " with Numeric " << Numeric << endb;
        exit(0);
   }

   cout << "Added Client with Numeric: " << Numeric << " NickName: " << NickName << " Account: " << Account <<
           " UserName: " << UserName << " HostName: " << HostName << " B6IP: " << B64IP << " Modes: " << Modes <<
           " TimeStamp: " << TimeStamp << " HopCount: " << HopCount << endl << "UserInfo: " << UserInfo << endl;
}

} // namespace eNetworks

