/*
 * ConfParser.cpp
 * Author: Alan Alvarez, <clsk@localnet.com>. (clsk@IRC)
 * Copyright (C) 2003 Gbot Project. <clsk@localnet.com>
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

#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

#include "tools.h"
#include "ConfParser.h" // class ConfParser declared.

using namespace std;

namespace eNetworks
{

ConfParser::ConfParser(const string &file, string &errors, int &errorns) :
nick("E"),
clientinfo("/msg E help"),
serverinfo("Electronic Channel Services"),
servername("eChan.vodanet.org"),
username("eChan"),
uplink("127.0.0.1"),
port("4400")
{
 errors = "";
 errorns = 0;

 if (file == "")
  cfile = "gbot.conf";
 else
  cfile = file;

 Parser(errors, errorns);
}

// errors = "linerror:where:errormsg:syntax;"
void ConfParser::Parser(string &errors, int &errorns)
{
  
  struct stat sb;
  if (stat(cfile.c_str(), &sb) == -1)
  {
    string errmsg = "Could not open " + cfile; 
    perror(errmsg.c_str());
    exit(1);
  }
 
 int cline = 0; // this var will hold number of the line that is curretnly in empty

 string empty; // getline() will put the line in this std::string variable
 ifstream ifs(cfile.c_str()); // Openning Conf file
 if (!ifs.is_open())
 {
   cout << "Could not open " << cfile << endl;
   exit(1);
 }
        while (getline(ifs, empty)) // checking every line to see if it has one of the information we need
         {
           cline++; // couting lines.

                 if(empty.substr(0,6) == "NICK =") // got nickname? no spaces
                  {
                    if (empty[6] != ' ')
                     { 
                       Send_Error(IntToString(cline), "NICK", ERR_SYNTAX, NICK_SYNTAX, errors);
                       errorns++;
                     }

                    else
                     {
                       empty = empty.substr(empty.find("=")+2); // We get the whole line so lets get rid of "NICK ="
                       empty = empty.substr(0,empty.find(";")); // ignoring everything after ";"
                     
                       if (empty.find(" ") != string::npos)
                        {
                          Send_Error(IntToString(cline), "NICK", ERR_SPACES, NICK_SYNTAX, errors);
                          errorns++;
                        }
                       else
                        {
                          nick = empty;
                        }
                     }
                  }

                 else if (empty.substr(0,12) == "CLIENTINFO =") // got irc name? 
                  {
                     if (empty[12] != ' ')
                      {
                        Send_Error(IntToString(cline), "CLIENTINFO", ERR_SYNTAX, NAME_SYNTAX, errors);
                        errorns++; // another error found. :/
                      }
                     else
                      {
                        empty = empty.substr(empty.find("=")+2); 
                        clientinfo = empty.substr(0,empty.find(";"));
                      }
                  }

                 else if (empty.substr(0,12) == "SERVERINFO =") // got irc name?
                  {
                     if (empty[12] != ' ')
                      {
                        Send_Error(IntToString(cline), "SERVERINFO", ERR_SYNTAX, NAME_SYNTAX, errors);
                        errorns++; // another error found. :/
                      }
                     else
                      {
                        empty = empty.substr(empty.find("=")+2);
                        serverinfo = empty.substr(0,empty.find(";"));
                      }
                  }

                 else if (empty.substr(0,10)== "USERNAME =") // got username? no more than 9 characters and no spaces
                  {
                     if (empty[10] != ' ')
                      {
                        Send_Error(IntToString(cline), "USERNAME", ERR_SYNTAX, USERNAME_SYNTAX, errors);
                        errorns++; // another error found. :/
                      }
                     else
                      { 
                        empty = empty.substr(empty.find("=")+2); 
                        empty = empty.substr(0,empty.find(";"));
                        if (empty.length() > 10)
                         {
                           Send_Error(IntToString(cline), "USERNAME", ERR_LENGTH, USERNAME_SYNTAX, errors);
                         }
                        else if (empty.find(" ") != string::npos) 
                         {
                           Send_Error(IntToString(cline), "USERNAME", ERR_SPACES, USERNAME_SYNTAX, errors);
                           errorns++;
                         }
                        else
                         {   
                           username = empty;
                         }
                      }
                  }

                 else if (empty.substr(0,8)== "UPLINK =") // got irc server? no spaces
                  {
                     if (empty[8] != ' ')
                      {
                        Send_Error(IntToString(cline), "UPLINK", ERR_SYNTAX, SERVER_SYNTAX, errors);
                        errorns++; // another error found. :/  
                      }
                     else
                      {
                        empty = empty.substr(empty.find("=")+2);
                        empty = empty.substr(0,empty.find(";")); // ignoring everything after ";"
                          if (empty.find(" ") != string::npos)
                           {
                             Send_Error(IntToString(cline), "UPLINK", ERR_SPACES, SERVER_SYNTAX, errors); 
                             errorns++;
                           }
                          else
                           {
                             uplink = empty;
                           }
                       } 
                  } 
                 else if (empty.substr(0,10)== "HOSTNAME =") // got irc server? no spaces
                  {
                     if (empty[10] != ' ')
                      {
                        Send_Error(IntToString(cline), "HOSTNAME", ERR_SYNTAX, SERVER_SYNTAX, errors);
                        errorns++; // another error found. :/
                      }
                     else
                      {
                        empty = empty.substr(empty.find("=")+2);
                        empty = empty.substr(0,empty.find(";")); // ignoring everything after ";"
                          if (empty.find(" ") != string::npos)
                           {
                             Send_Error(IntToString(cline), "HOSTNAME", ERR_SPACES, SERVER_SYNTAX, errors);
                             errorns++;
                           }
                          else
                           {
                             hostname = empty;
                           }
                       }
                  }

          
                 else if (empty.substr(0,12)== "SERVERNAME =") // got irc server? no spaces
                  {
                     if (empty[12] != ' ')
                      {
                        Send_Error(IntToString(cline), "SERVERNAME", ERR_SYNTAX, SERVER_SYNTAX, errors);
                        errorns++; // another error found. :/
                      }
                     else
                      {
                        empty = empty.substr(empty.find("=")+2);
                        empty = empty.substr(0,empty.find(";")); // ignoring everything after ";"
                          if (empty.find(" ") != string::npos)
                           {
                             Send_Error(IntToString(cline), "SERVERNAME", ERR_SPACES, SERVER_SYNTAX, errors);
                             errorns++;
                           }
                          else
                           {
                             servername = empty;
                           }
                       }
                  }

                 else if (empty.substr(0,6)== "PORT =") // got port? only numbers permitted with no spaces
                  {
                     if (empty[6] != ' ')
                      {
                        Send_Error(IntToString(cline), "PORT", ERR_SYNTAX, PORT_SYNTAX, errors);
                        errorns++; // another error found. :/
                      }
                     else
                      {
                        empty = empty.substr(empty.find("=")+2);
                        empty = empty.substr(0,empty.find(";")); // ignoring everything after ";"
                         if (empty.find(" ") != string::npos)
                          {
                            Send_Error(IntToString(cline), "PORT", ERR_SPACES, PORT_SYNTAX, errors);
                            errorns++;
                          }
                         else if (find_if(empty.begin(), empty.end(), not1(ptr_fun<int, int>(isdigit))) != empty.end())
                          {   
                            Send_Error(IntToString(cline), "PORT", ERR_ONLYN, PORT_SYNTAX, errors);
                            errorns++;
                          }
                         else
                          {
                            port = empty;
                          }
                       }
                  }

                 else
                  {
                   continue;
                  }
         }
 ifs.close(); // Closing cfile
} // end praser()
  

void ConfParser::Send_Error(const string &ln, // lines as string
                            const string &where, // error msg
                            const string &err, // what line?
                            const string &syntax, // right syntax
                            string &errors // returning?
                           )
{
  errors += ln;
  errors += ":";
  errors += where;
  errors += err;
  errors += syntax;  // correct syntax
  errors += ";\n";
 
// return errors;
}  

} // namespace eNetworks
