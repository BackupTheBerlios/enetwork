#include <iostream>
#include <ctime>
#include <string>

#include "Crypto.h"

using namespace eNetworks;
using namespace std;

int main()
{
   srand((clock() + time(0)) * 1000000);
//   string tmp = Crypto::EncryptPassword("mypass");
//   cout << tmp << endl;
   cout << "cGQDowc3f02b41083441c569f1d8cb24dce78712" << endl;
   cout << Crypto::MatchPassword("23031985", Crypto::EncryptPassword("mypass")) << endl;

return 0;
}
