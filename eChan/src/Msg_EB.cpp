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
   	debug << "ServerSrc is NULL in Msg_EB::Parser().";
   	exit(0);
   }

   (*eSock) << ServerSrc->GetNumeric() << " " << Tokens::END_OF_ACK << "\r\n";
   cout << "[OUT]: " <<  ServerSrc->GetNumeric() << " " << Tokens::END_OF_ACK << endl;
}

} // namespace eNetworks
