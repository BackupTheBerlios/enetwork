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

#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>

using std::cout;
using std::endl;

#include "Client.h"
#include "tools.h"
#include "ConfParser.h"
#include "Server.h"
#include "SocketException.h"
#include "Socket.h"
#include "P10Tokens.h"
#include "Msg_B.h"

using namespace std;

namespace eNetworks
{

int StringToInt(string str) // string to int
{
  stringstream strm(str);
  int rint;
  strm >> rint; // translating from string to int...

return rint;
}

// This function will change a string to an int.
// on error returns "ERR"
string IntToString(const int &x)
{
 ostringstream o;
   if (o << x)
    {
      return o.str();
    }
   else
    {
    return "ERR";
    }
} // end IntToString()

unsigned int b64Tob10(const string &b64)
{
   unsigned int rv = 0; // return value.

   unsigned int j = 0;
   for (unsigned int i = b64.size(); i > 0; i--)
   {
        if (b64Table.find(b64[i-1]) == string::npos)
         return 0;

        rv += static_cast<unsigned int>(pow(static_cast<double>(64), static_cast<int>(j)) * b64Table.find(b64[i-1]));
        j++;
   }

return rv;
}

bool IsDigit(const string &str)
{
  if(find_if(str.begin(), str.end(), not1(ptr_fun<int, int>(isdigit))) != str.end())
   return false;
  else
   return true;
}

bool IsCommand(string &inbuffer, string &command)
{
  if (inbuffer.find("\r\n") != string::npos)
  {
    command = inbuffer.substr(0,inbuffer.find("\r\n")); 
    inbuffer = inbuffer.substr(inbuffer.find("\r\n")+2);
    return true;
  }
  else if (inbuffer.find("\n") != string::npos)
  {
    command = inbuffer.substr(0,inbuffer.find("\n"));
    inbuffer = inbuffer.substr(inbuffer.find("\n")+1);
    return true;
  }

return false;
}

void CreateLocals()
{ 
   string errors;
   int errnos;
   ConfParser eConf("eChan.conf", errors, errnos);

   LocalServer = new Server(eConf.GetNumeric(), eConf.GetServerName(), "", eConf.GetServerInfo(), time(0), time(0), 1, 's');

   if (LocalServer == NULL)
   {
   	cout << "Could not create server: " << eConf.GetServerName() << endl;
   	exit(0);
   }

   LocalClient = new Client(eConf.GetNumeric()+"AAC", eConf.GetNick(), "", eConf.GetUserName(), eConf.GetHostName(),
                            "DAqAoB", "idk", eConf.GetClientInfo(), time(0), 1);

   if (LocalClient == NULL)
   {
   	cout << "Could Not add client " << eConf.GetNick() << endl;
        exit(0);
   }

   try
   {
   	eSock = new Socket(eConf.GetUpLink(), StringToInt(eConf.GetPort()));
   }
   catch (SocketException &sockerr)
   {
   	sockerr.log();
   	sockerr.fix();
   }
}

void login()
{
   try
   {
        // loging to IRC server
        cout << "logging in" << endl;
        (*eSock) << "PASS :DAPASS\r\n";
        cout << "[OUT]: PASS :DAPASS" << endl;

       (*eSock) << Tokens::PRESERVER << " " << LocalServer->GetName() << " " << LocalServer->GetHopCount() <<
            " " << LocalServer->GetStartTime() << " " << LocalServer->GetLinkTime() <<
            " J10 " << LocalServer->GetNumeric() << "AAC" << " +" << LocalServer->GetFlag() << " :" <<
            LocalServer->GetDescription() << "\r\n";

        cout << "[OUT]: " << Tokens::PRESERVER << " " << LocalServer->GetName() << " " << 
                LocalServer->GetHopCount() << " " << LocalServer->GetStartTime() << " " << 
                LocalServer->GetLinkTime() << " J10 " << LocalServer->GetNumeric() << "AAC" << " +" <<
                LocalServer->GetFlag() << " :" << LocalServer->GetDescription() << endl;

        (*eSock) << LocalServer->GetNumeric() << " " << Tokens::NICK << " " << LocalClient->GetNickName() << " " <<
            LocalClient->GetHopCount() << " " << LocalClient->GetTimeStamp() << " " <<
            LocalClient->GetUserName() << " " << LocalClient->GetHostName() << " " <<
            "+idk" << " " << LocalClient->GetB64IP() << " " << LocalClient->GetNumeric() <<
            " :" << LocalClient->GetUserInfo() << "\r\n";

        cout << "[OUT]: " << LocalServer->GetNumeric() << " " << Tokens::NICK << " " << 
                LocalClient->GetNickName() << " " << LocalClient->GetHopCount() << " " << 
                LocalClient->GetTimeStamp() << " " << LocalClient->GetUserName() << " " << 
                LocalClient->GetHostName() << " " << "+idk" << " " << LocalClient->GetB64IP() << " " <<
                LocalClient->GetNumeric() << " :" << LocalClient->GetUserInfo() << endl;


        (*eSock) << LocalServer->GetNumeric() << " " << Tokens::END_OF_BURST << "\r\n";
     
        cout << "[OUT]: " << LocalServer->GetNumeric() << " " << Tokens::END_OF_BURST << endl;
   } catch(SocketException &sockerr)
   {
        sockerr.log();
        sockerr.fix();
   }
}

} // namespace eNetworks
