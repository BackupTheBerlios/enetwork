#include <string>
#include "InBuffer.h"


namespace eNetworks {

InBuffer::InBuffer(const string &_Msg): Buffer(_Msg), Msgs()
{
   Digest();
}


void InBuffer::Digest()
{
   while (buffer.find('\n') != string::npos || buffer.find("\r\n") != string::npos || buffer.find('\r') != string::npos)
   {

        if (buffer.find('\n') != string::npos)
        {
           Msgs.push_back(buffer.substr(0,buffer.find('\n')));
           buffer = buffer.substr(buffer.find('\n')+1);
        }
   	else if (buffer.find("\r\n") != string::npos)
   	{
   	   Msgs.push_back(buffer.substr(0,buffer.find("\r\n")));
   	   buffer = buffer.substr(buffer.find("\r\n")+2);
   	}
   	else if (buffer.find('\r') != string::npos)
   	{
   	   Msgs.push_back(buffer.substr(0,buffer.find('\r')));
   	   buffer = buffer.substr(buffer.find('\r')+1);
   	}
   }
}

} // namespace eNetworks
