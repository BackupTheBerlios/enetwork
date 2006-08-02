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

#ifndef ELECTRONIC_NETWORKS__CRYPTO_H
#define ELECTRONIC_NETWORKS__CRYPTO_H

#include <string>
#include <iostream>

#include "MD5.h"

namespace eNetworks
{

class Crypto
{
   public:
   	
   	static bool MatchPassword(const std::string& plaintext, const std::string& cyphertext)
   	{
   	   // This is temporary until we find a better solution.
   	   std::string tmp = cyphertext.substr(0,8) + Encrypt(plaintext, cyphertext.substr(0,8));
   	   for (int i = 0; i < tmp.length(); i++)
   	   {
   	   	if (tmp[i] != cyphertext[i])
   	   	{
   	   	   // std::cout << tmp[i] << " != " << cyphertext[i] << std::endl;
   	   	   return false;
   	   	}
   	   }

   	   return true;


//   	   return Encrypt(plaintext, cyphertext.substr(0,8)) == cyphertext;
   	}

   	static std::string EncryptPassword(const std::string& plaintext)
   	{
   	   std::string salt = GenerateSalt();
   	   return salt + Encrypt(plaintext, salt);
   	}

//   private:
   	static std::string GenerateSalt();
   	static std::string Encrypt(const std::string& plaintext, const std::string& salt);
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__CRYPTO_H
