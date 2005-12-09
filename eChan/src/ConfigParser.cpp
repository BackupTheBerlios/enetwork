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

#include <cstdlib>
#include <string>
#include <fstream>

#include "ConfigParser.h"
#include "debug.h"

using std::string;
using std::getline;
using std::ifstream;

namespace eNetworks
{

ConfigParser::ConfigParser(const std::string& _ConfigFile) : ConfigMap(), ConfigFile(_ConfigFile)
{
}

void ConfigParser::ParseConfigFile()
{
   ifstream ifsConfigFile(ConfigFile.c_str()); // Opening Configuration file
   if (!ifsConfigFile.is_open())
   {
   	debug << "ConifgParser Error: Could not open " << ConfigFile << endb;
   	exit(0);
   }

   unsigned int intCurrentLine = 0;
   string strCurrentLine;
   while(getline(ifsConfigFile, strCurrentLine))
   {    
   	intCurrentLine++; // start with line 1.

   	if (strCurrentLine == "")
   	   continue;

   	// replace this with a strip function.
   	while(strCurrentLine[0] == ' ')
   	{
   	   strCurrentLine = strCurrentLine.substr(1);
   	}

   	// Comment line. Ignore.
   	if (strCurrentLine[0] == '#')
   	   continue;

   	if (!IsItem(strCurrentLine.substr(0, strCurrentLine.find(" "))))
   	{
   	   // handle error "Unrecognizable configuration"
   	   debug << "Line " << intCurrentLine << ": Unrecognizable configuration." << endb;
   	   continue;
   	}

   	string strItem = strCurrentLine.substr(0, strCurrentLine.find(" "));
   	strCurrentLine = strCurrentLine.substr(strItem.length()+1);

   	// replace this with a strip function.
        while(strCurrentLine[0] == ' ')
        {
           strCurrentLine = strCurrentLine.substr(1);
        }

   	if (strCurrentLine[0] != '=')
   	{
   	   // handle error "Expected '=' Token."
   	   debug << "Line " << intCurrentLine << ": Expected \'=\' Token." << endb;
   	   continue;
   	}
   	strCurrentLine = strCurrentLine.substr(1);

        // replace this with a strip function.
        while(strCurrentLine[0] == ' ')
        {
           strCurrentLine = strCurrentLine.substr(1);
        }
   	
   	if (strCurrentLine[0] != '\"')
   	{
   	   // handle error "Expected '\"' Token."
   	   debug << "Line " << intCurrentLine << ": Expected \'\"\' Token (0x01)." << endb;
   	   continue;
   	}

   	// Format is ITEM = "CONFIGURATION"
   	string strConfiguration = strCurrentLine.substr(1);
   	if (strConfiguration.find('\"') != string::npos)
   	{
   	   for (unsigned int i = 0; i < strConfiguration.length(); i++)
   	   {
   	   	if ('\"' == strConfiguration[i] && '\\' != strConfiguration[i-1])
   	   	   strConfiguration = strConfiguration.substr(0, i);
   	   }
   	}
   	else
  	{
   	   // handle error "Expected '\"' Token"
   	   debug << "Line " << intCurrentLine << ": Expected \'\"\' Token (0x02)." << endb;
   	   continue;
   	}
   	SetConfiguration(strItem, strConfiguration);
   }
 
   ifsConfigFile.close();
}


bool ConfigParser::IsItem(const string& Item)
{
   ConfigMapType::iterator iterConfigMap = ConfigMap.find(Item);

   if (ConfigMap.end() == iterConfigMap)
   	return false;

   // else
   return true;
}

std::string ConfigParser::GetConfiguration(const string& Item)
{
   ConfigMapType::iterator iterConfigMap = ConfigMap.find(Item);

   if (ConfigMap.end() == iterConfigMap)
    return "";
   // else
   return iterConfigMap->second;
}

void ConfigParser::SetConfiguration(const string& Item, const string& Configuration)
{
   ConfigMapType::iterator iterConfigMap = ConfigMap.find(Item);

   if (ConfigMap.end() != iterConfigMap)
   	iterConfigMap->second = Configuration;
}

bool ConfigParser::InsertItem(const string& Item, const string& Configuration)
{
   return ConfigMap.insert(ConfigMapType::value_type(Item,Configuration)).second;
}

} // namespace eNetworks
