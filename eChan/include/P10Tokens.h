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

#ifndef ELECTRONIC_NETWORKS__P10TOKENS_H
#define ELECTRONIC_NETWORKS__P10TOKENS_H

#include <string>
#include <map>

namespace eNetworks
{

// This class holds P10 Tokens.
class Tokens
{
   public:
   	Tokens() : TokensMap() {}
   	~Tokens() {}

   	// List of handled Tokens.
   	enum Token 
   	{
   	   NONE = 0, // Means invalid token. Used for GetToken().
   	   SERVER,
   	   NICK,
   	   B,
   	   BURST,
   	   JOIN,
   	   PART,
   	   PING,
   	   END_OF_BURST,
   	   ACCOUNT,
   	   CREATE,
   	   QUIT,
   	   SQUIT,
   	   MODE,
   	   KICK,
   	   CLEARMODE,
   	   TOPIC,
   	   OPMODE,
   	   PRIVMSG,
   	   NOTICE
   	};

   	typedef Token TokenType;
   	typedef std::map<std::string, TokenType> TokensMapType;

   	bool AddToken(const std::string& TokenString, const TokenType& _Token);
   	TokenType GetToken(const std::string& TokenString);

   private:
   	TokensMapType TokensMap;
};

extern Tokens* eTokens;

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__P10TOKENS_H
