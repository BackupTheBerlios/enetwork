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

#ifndef ELECTRONIC_NETWORKS__MSGMONITOR_H
#define ELECTRONIC_NETWORKS__MSGMONITOR_H

#include <list>
#include <utility>

#include "Bot.h"
#include "MsgSource.h"
#include "MsgTokenizer.h"
#include "P10Tokens.h"

namespace eNetworks
{
class MsgMonitor
{
   public:
   	static void AddMonitor(const Tokens::Token& _Token, Bot* _Bot);

   protected:
   	MsgMonitor() {}
   	static void NotifyMonitors(const Tokens::Token& _Token, const MsgSource& Source, const MsgTokenizer& Parameters);

   private:
   	typedef std::pair<Tokens::Token, Bot*> MonitorType;
   	typedef std::list<MonitorType> MonitorListType;
   	static MonitorListType mList;
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__MSGMONITOR_H
