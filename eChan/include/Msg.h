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

#ifndef ELECTRONIC_NETWORKS__MSG_H
#define ELECTRONIC_NETWORKS__MSG_H

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
//                    SERVER Token. (A server introducing itself)
// -------------------------------------------------------------------------------
class PreServerMsg : public Msg
{
 public: 
	PreServerMsg(const std::string &aCommand, const std::string &aToken) : Msg(aCommand, aToken) {}     
 	virtual ~PreServerMsg() {}						

	virtual void Parser();
        
};

// -------------------------------------------------------------------------------
//                    S Token. (A server introducing another server)
// -------------------------------------------------------------------------------
class Msg_S : public Msg
{
   public:
   	Msg_S(const std::string &aCommand, const std::string &aToken) : Msg(aCommand, aToken) {}

   	virtual ~Msg_S() {}
   	virtual void Parser();
};

// -------------------------------------------------------------------------------
//                    N Token. (A server introducing a client)
// -------------------------------------------------------------------------------
class Msg_N : public Msg
{
   public:
        Msg_N(const std::string &aCommand, const std::string &aToken) : Msg(aCommand, aToken) {}

        virtual ~Msg_N() {}
        virtual void Parser();
};


} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__MSG_H
