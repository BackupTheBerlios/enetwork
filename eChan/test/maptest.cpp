#include <map>
#include <string>
#include <iostream>
#include <utility>

using std::map;
using std::string;
using std::cout;
using std::endl;
using std::pair;

int main()
{
   map<string, string> MyMap;

   MyMap.insert(pair<string, string>("clsk", "bla bla"));
   MyMap.insert(pair<string, string>("hugo", "gay"));
   MyMap.insert(pair<string, string>("danny", "otro gay"));
 
   cout << MyMap.find("hugo")->second << endl;

return 0;
}
