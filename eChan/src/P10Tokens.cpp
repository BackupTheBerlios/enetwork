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

#include <map>
#include <string>

#include "P10Tokens.h"

namespace eNetworks
{

bool Tokens::AddToken(const std::string& TokenString, const TokenType& _Token)
{
   return TokensMap.insert(TokensMapType::value_type(TokenString, _Token)).second == false;
}

Tokens::TokenType Tokens::GetToken(const std::string& TokenString)
{
   // try to find the token.
   TokensMapType::iterator iterTokensMap = TokensMap.find(TokenString);

   // If we can't find it return Tokens::NONE
   if (TokensMap.end() == iterTokensMap)
    return Tokens::NONE;

   return iterTokensMap->second;
}

Tokens* eTokens = 0;

} // namespace eNetworks
