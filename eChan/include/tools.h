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

#ifndef ELECTRONIC_NETWORKS__TOOLS_H
#define ELECTRONIC_NETWORKS__TOOLS_H

#include <string>
#include <vector>

#include "ConfigParser.h"

namespace eNetworks
{

static const std::string b64Table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789[]";

// Casting functions.
int StringToInt(std::string);
std::string IntToString(const int &);
unsigned int b64Tob10(const std::string &b64);

// Info functions
bool IsDigit(const std::string &str);

// misc functions.
void login(ConfigParser& theConfigParser);

// structs

/** This struct was made by Dan Karrels for the GNUworld project.
 *  The copyright notice at the top of this file does NOT apply to this struct. 
 *  However, this struct was released under the GNU GPL in a file in 
 *  the gnuworld project.
 *
 * Case insensitive comparison struct for use by STL structures/algorithms.
 */
struct noCaseCompare
{
inline bool operator()( const std::string& lhs, const std::string& rhs ) const
        {
        return (strcasecmp( lhs.c_str(), rhs.c_str() ) < 0) ;
        }
} ;


} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__TOOLS_H
