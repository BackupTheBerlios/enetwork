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

#ifndef ELECTRONIC_NETWORKS__MSG_H
#define ELECTRONIC_NETWORKS__MSG_H

#include "MsgTokenizer.h"
#include "MsgSource.h"

/*
   NOTES:

   Every class derived from Msg should have an overriden void Parser() function.

*/

namespace eNetworks
{


// -------------------------------------------------------------------------------
//                               Base Msg Class
// -------------------------------------------------------------------------------
class Msg
{
  public:
	// Takes care of setting the members no matter what kind of Msg it is.
	Msg(const MsgSource& _Source, const MsgTokenizer& _Parameters) : Source(_Source), Parameters(_Parameters) {} 
	virtual ~Msg() {};

	virtual void Parser() = 0;

  protected:

   	MsgSource Source;
	MsgTokenizer Parameters; // These are the parameters that go after the Token all tokenized.
};


} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__MSG_H
