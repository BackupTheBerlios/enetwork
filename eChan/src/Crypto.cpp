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

#include <string>
#include <sstream>
#include <iomanip>

#include "Crypto.h"
#include "MD5.h"

using std::string;
using std::stringstream;
using std::ends;

namespace eNetworks
{

string Crypto::GenerateSalt()
{
const char validChars[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.$*_";

string salt;
for( unsigned short int i = 0 ; i < 8 ; ++i )
        {
        int randNo = 1 + (int) (64.0 * rand() / (RAND_MAX + 1.0) );
        salt += validChars[ randNo ] ;
        }

return salt;
}

// Extracted from gnuworld project cservice::CryptPass.
string Crypto::Encrypt(const string& plaintext, const string& salt)
{
/* Work out a MD5 hash of our salt + password */
md5             hash; // MD5 hash algorithm object.
md5Digest       digest; // MD5Digest algorithm object.

stringstream output;
string newPass;
newPass = salt + plaintext;

hash.update( (const unsigned char *)newPass.c_str(),
        newPass.size() );
hash.report( digest );

/* Convert to Hex */
int data[ MD5_DIGEST_LENGTH ] = { 0 } ;
for( size_t ii = 0; ii < MD5_DIGEST_LENGTH; ii++ )
        {
        data[ii] = digest[ii];
        }

output << std::hex;
output.fill('0');
for( size_t ii = 0; ii < MD5_DIGEST_LENGTH; ii++ )
        {
        output << std::setw(2) << data[ii];
        }
output << ends;

return string( salt + output.str()  );
}

} // namespace eNetworks
