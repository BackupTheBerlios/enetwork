#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

string cs = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

string MyCrypt(const string &plain, int key = rand() % 0xffff);

int main()
{
   srand(RAND_MAX);

   cout << MyCrypt("yathisisatest") << endl;

return 0;   
}

string MyCrypt(const string &plain, int key)
{
cout << key << endl;
   
   if(plain.length() == 0 || plain.find(" ") != string::npos)
    return "";

   if (plain.length() == 1 && (plain == "" || plain[0] == ' '))    
    return "";

   string crypt;   

   for (int i = 0; i < plain.length(); i++) 
   {
	if ((cs.find(plain[i]) + key) >= cs.length())
	{
	   int tmp = 0;
	   tmp = (cs.find(plain[i]) + key) - cs.length();
	   while(tmp >= cs.length())
             tmp = tmp - cs.length();
	   
	   crypt += cs[tmp];
	}
	else
	{
	   crypt += cs[cs.find(plain[i]) + key];
	}
   }
return crypt;
}
