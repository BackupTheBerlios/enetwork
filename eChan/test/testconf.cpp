#include <iostream>
#include <string>

#include "ConfParser.h"

using std::cout;
using std::endl;
using std::string;

int main()
{

   string errors;
   int errnos = 0;
   ConfParser eConf("eChan.conf", errors, errnos); 
 
   if (errnos)
    cout << errors << endl;

   cout << "Nick: " << eConf.GetNick() << endl;
   cout << "ClientInfo: " << eConf.GetClientInfo() << endl;
   cout << "HostName: " << eConf.GetHostName() << endl;
   cout << "ServerName: " << eConf.GetServerName() << endl;
   cout << "ServerInfo: " << eConf.GetServerInfo() << endl;
   cout << "UserName: " << eConf.GetUserName() << endl;
   cout << "UpLink: " << eConf.GetUpLink() << endl;
   cout << "Port: " << eConf.GetPort() << endl;

return 0;
}
