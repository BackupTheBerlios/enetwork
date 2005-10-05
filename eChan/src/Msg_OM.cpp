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
#include <iostream>

#include "Msg_M.h"
#include "Msg_OM.h"
#include "Network.h"
#include "debug.h"

using std::string;
using std::cout;
using std::endl;

namespace eNetworks
{

void Msg_OM::Parser()
{
   if (Source.IsClient())
   {
   	if (false == eNetwork->FindClientByNumeric(Source.GetNumeric())->IsOper())
   	   debug << Source.GetName() << " issuing OPMODE but is not Oper." << endb;
   }

   // Treat this as a MODE message.
   Msg_M theMsg(Source, Parameters);
   theMsg.Parser();
}

} // namespace eNetworks

