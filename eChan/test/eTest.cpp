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


#include <iostream>
#include <ctime>

#include "Network.h"
#include "Client.h"

using std::cout;
using std::endl;
using eNetworks::eNetwork;
using eNetworks::Channel;
using eNetworks::Client;

int main()
{
   eNetwork = new eNetworks::Network();
   
   // Try to add new server.   
   if (eNetwork->AddServer("AB", "eChan.vodanet.org", "AZ", "Electronic Channel Services", time(0), time(0), 1, '0'))
    cout << "Added eChan.vodanet.org" << endl;
   else 
    cout << "could not add eChan.vodanet.org" << endl;

   if (eNetwork->FindServerByNumeric("AB") == NULL)
    cout << "Could not find server with numeric AB" << endl;
   else
    cout << "Found Server with numeric AB that has name: " << eNetwork->FindServerByNumeric("AB")->GetName() << endl; 

   if (eNetwork->FindServerByName("eChan.vodanet.org") == NULL)
    cout << "Could not find server eChan.vodanet.org" << endl;
   else
    cout << "found server eChan.vodanet.org with numeric: " <<
            eNetwork->FindServerByName("eChan.vodanet.org")->GetNumeric() << endl;

   cout << "eNetwork->ServerCount before delete: " << eNetwork->ServerCount() << endl;

   // client...

   cout << eNetwork->ClientCount() << endl;


   if(eNetwork->AddClient("ABAAA", "E", "", "cservice", "vodanet.org", "b64ip", "idk", "/msg E help", time(0), 1))
    cout << "Added Client E" << endl;
   else 
    cout << "Could not add client E" << endl;

/*
   if (eNetwork->DelClientByNumeric("ABAAA"))
    cout << "Deleted Client with numeric ABAAA" << endl;
   else
    cout << "Couldn't delete Client with numeric ABAAA" << endl;
*/

   Client *eClient = eNetwork->FindClientByNickName("E");
 
   eClient->AddMode('x');
   eClient->DelMode('x');
 
   if (eClient->HasMode('x'))
    cout << "the user has mode x" << endl;
   else
    cout << "the user doesn't have mode x" << endl;


   if (eClient != NULL)
    cout << "Found client " <<  eClient->GetNickName() << " with numeric: " << eClient->GetNumeric() << endl;
   else
    cout << "Could not find Client E" << endl;

   if (eNetwork->AddChannel("#coder-com", "", "tn", "", 0, time(0)))
    cout << "Added channel #coder-com" << endl;
   else 
    cout << "Could not add channel #coder-com" << endl;

   Channel *ChannelPtr = eNetwork->FindChannel("#coder-com");

   if (ChannelPtr == NULL)
    cout << "Channel #coder-com doesn't exist" << endl;
   else
   {
    	if (ChannelPtr->AddChannelClient(eClient, "o"))
   	 cout << "Added Client: " << eClient->GetNickName() << endl;
   	else
   	 cout << "Could not add eClient" << endl;
   }

   cout << ChannelPtr->ChannelClientCount() << endl;

   if (eNetwork->DelServerByName("eChan.vodanet.org"))
    cout << "Deleted server with numeric AB" << endl;
   else
    cout << "Could not delete server with numeric AB" << endl;

   cout << "eNetwork->ServerCount after delete: " << eNetwork->ServerCount() << endl;

   cout << eNetwork->ClientCount() << endl;

   cout << ChannelPtr->ChannelClientCount() << endl;

return 0;
}
