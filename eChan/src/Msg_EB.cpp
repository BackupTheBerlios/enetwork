#include <string>
#include <iostream>

#include "debug.h"
#include "Msg_EB.h"
#include "Socket.h"
#include "P10Tokens.h"
#include "Server.h"

using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

void Msg_EB::Parser()
{
   if (ServerSrc == NULL)
   {
   	debug << "ServerSrc is NULL in Msg_EB::Parser()." << endb;
   	exit(0);
   }

   (*eSock) << LocalServer->GetNumeric() << " " << Tokens::END_OF_ACK << "\r\n";
   cout << "[OUT]: " <<  LocalServer->GetNumeric() << " " << Tokens::END_OF_ACK << endl;

/*
   (*eSock) << LocalServer->GetNumeric() << " G !1071288273.976939 test.vodanet.org 1071288273.976939\r\n";
   cout << "[OUT]: " << LocalServer->GetNumeric() << " G !1071288273.976939 test.vodanet.org 1071288273.976939" << endl;
*/

}

} // namespace eNetworks
