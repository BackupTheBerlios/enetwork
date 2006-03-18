/*
 * eChan - Electronic Channel Services.
 * Copyright (C) 2003-2006 Alan Alvarez.
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

#include <string>
#include <iostream>

#include "MsgTokenizer.h"
#include "debug.h"

using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

// TODO: This algorithm needs to be improved...
MsgTokenizer::MsgTokenizer(const std::string &aCommand, const char &Terminator, const char &Delimiter)
{
//   cout << "string aCommand: " << aCommand << endl;
//   const char Delimiter = ' ';
   if (aCommand == "")
   	return;

   // If we don't find the delimiter just push back one string and return. if aCommand.length() == 0 just return.
   if (aCommand.find(Delimiter) == string::npos)
    if (aCommand.length() == 0)
     return;
    else 
    {
    	Tokens.push_back(aCommand);
    	return;
    }

   string FullString = aCommand;

   // Check if the first character is the delimiter. If the only character in the string is a delimiter return.
   if (FullString[0] == Delimiter)
    if (FullString.length() == 1)
     return;
    else
     FullString = FullString.substr(1);


   while(true)
   {    // we should never get here, but just in case.
   	if (FullString.length() == 0)
   	{
   	   debug << "reached length 0 in MsgTokenizer." << endb;
   	   return;
   	}
   	else if (FullString[0] == Delimiter)
   	{
   	   FullString.erase(0,1);
   	   continue;
   	}
        else if (Terminator != NULL && FullString[0] == Terminator)
        {
   	   Tokens.push_back(FullString.substr(1));
   	   break;
   	}
   	else if (FullString.find(Delimiter) == string::npos)
   	{
           Tokens.push_back(FullString);
   	   break;
   	}
   	else 
   	{   	   
   	   Tokens.push_back(FullString.substr(0, FullString.find(Delimiter)));

   	   if (FullString.length() == FullString.find(Delimiter)+1)
   	    break;
   	   else
   	    FullString = FullString.substr(FullString.find(Delimiter)+1);
   	    // continue;
   	}
   }

   // Get rid of any extra space character at the end of the message.
   if (Tokens.size() > 0)
   {
   	string LastString = Tokens[Tokens.size()-1];

   	while (LastString.length() != 0 && LastString[LastString.length()-1] == ' ')
    	{
   	   LastString.erase(LastString.length()-1, 1);
   	}
   	
   	Tokens[Tokens.size()-1] = LastString;
   }
}

} // namespace eNetworks
