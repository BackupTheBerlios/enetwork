#include <iostream>
#include <string>
#include <unistd.h>

using std::string;
using std::cout;
using std::cin;
using std::endl;

// string MyCrypt(const string &plain, int key = rand() % 0xffff);

string MyCrypt(const string key);

int main()
{
   srand(RAND_MAX);

   cout << MyCrypt("yEathisisatest") << endl;

return 0;   
}

string MyCrypt(const string key)
{
   char salt[3];
   salt[0] = key[0];
   salt[1] = key[key.length()-1];
   salt[2] = '\0';

   return crypt(key.c_str(), salt);
}
