/*
 * ConfParser.h
 * Author: Alan Alvarez, <clsk@localnet.com>. (clsk@IRC)
 * Copyright (C) 2002-2003 Gbot Project. <clsk@localnet.com>
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


#ifndef ConfParser_H
#define ConfParser_H

#include <string>

namespace eNetworks
{

// Global Variables...

// *** Syntax ***
const std::string NICK_SYNTAX = "NICK = YourNick";
const std::string NAME_SYNTAX = "NAME = IRC Real Name";
const std::string USERNAME_SYNTAX = "USERNAME = ircuser";
const std::string SERVER_SYNTAX = "SERVER = 127.0.0.1";
const std::string PORT_SYNTAX = "PORT = 6667";

// *** Errors ***
const std::string ERR_SPACES = ":Cannot have spaces:";
const std::string ERR_SYNTAX = ":Syntax Error:";
const std::string ERR_LENGTH = ":Cannot have more than 10 chars long:"; // only for USERNAME
const std::string ERR_ONOFF = ":Correct values are on or off:";
const std::string ERR_ONLYN = ":Only numbers accepted:";
const std::string ERR_12_24 = ":Correct values are 12 or 24:";


class ConfParser
{

public:
  ConfParser(const std::string &file, std::string &errors, int &errorns); // constructor
  // we're going to fill these variables with the errors and the number of errors gotten.

        // accessors
        std::string GetNick() const {return nick;}
        std::string GetClientInfo() const {return clientinfo;}
        std::string GetHostName() const {return hostname;}
        std::string GetServerName() const {return servername;}
        std::string GetServerInfo() const {return serverinfo;}
        std::string GetUserName() const {return username;}
        std::string GetUpLink() const {return uplink;}
        std::string GetPort() const {return port;}

private:
        // other methods
        void ConfParser::Parser(std::string &errors, int &errorns);
        void Send_Error(const std::string &ln, // lines as string
                        const std::string &where, // error msg
                        const std::string &err, // what line?
                        const std::string &syntax, // right syntax
                        std::string &errors); // returning?                       


        std::string nick;
        std::string clientinfo;
        std::string hostname;
        std::string serverinfo; 
        std::string servername;
        std::string username;
        std::string uplink;
        std::string port;
        std::string cfile;
};

} // namespace eNetworks

#endif // ConfParser_H
