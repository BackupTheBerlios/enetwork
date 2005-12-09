/*
 * eChan - Electronic Channel Services.
 * Copyright (C) 2003-2005 Alan Alvarez.
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

#ifndef ELECTRONIC_NETWORKS__STRINGTOKENIZER_H
#define ELECTRONIC_NETWORKS__STRINGTOKENIZER_H

#include <string>
#include <vector>

namespace eNetworks
{

// This class will take a server message and split parameters into a std::vector of std::strings.
class MsgTokenizer
{
   public:

   	// Constructor.
   	// aCommand = The IRC Message you want to tokenize.
   	// Terminator = Normally Server<->Server messages use ':' 
   	//   	   	to specify that what follows is string that 
   	//   	   	is to be treated as one.
   	// Delimiter = The character that separates parameters.
   	MsgTokenizer(const std::string &aCommand, const char &Terminator = ':', const char &Delimiter = ' ');

   	// returns how many tokens were collected.
   	unsigned int size() const { return Tokens.size(); }

   	// returns a reference to the token stored at position.
   	std::string operator[](const unsigned int &position) const { return Tokens[position]; }

   private:
   	// Vector that holds tokens.
   	std::vector<std::string> Tokens;
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__STRINGTOKENIZER_H
