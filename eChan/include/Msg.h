/*
 * eChan - Electronic Channel Services.
 * Copyright (C) 2003 Alan Alvarez.
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

#ifndef Msg_H
#define Msg_H

#include <string>

#include "MsgTokenizer.h"

/*
   NOTES:

   Every class derived from Msg should have a overriden void Parser() function.

*/

namespace eNetworks
{

// foward declaration
struct Client;
struct Server;

// -------------------------------------------------------------------------------
//                               Base Msg Class
// -------------------------------------------------------------------------------
class Msg
{
  public:
		// Takes care of setting the members no matter what kind of Msg it is.
		Msg(const std::string &command, const std::string &aToken); // constructor 
		virtual ~Msg() {};

		virtual void Parser();

  protected:

		std::string Token;
		Client *ClientSrc;
		Server *ServerSrc;
		MsgTokenizer Parameters;
};


// -------------------------------------------------------------------------------
//                               SERVER Token.
// -------------------------------------------------------------------------------
class PreServerMsg : public Msg
{
 public: 
		PreServerMsg(const std::string &aCommand, const std::string &aToken) : Msg(aCommand, aToken) {}     
 		virtual ~PreServerMsg() {};						

		virtual void Parser();
        
};

} // namespace eNetworks

#endif // Msg_H
