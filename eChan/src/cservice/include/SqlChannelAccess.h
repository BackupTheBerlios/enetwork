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

#ifndef ELECTRONIC_NETWORKS__CSERVICE_SQLCHANNELACCESS_H
#define ELECTRONIC_NETWORKS__CSERVICE_SQLCHANNELACCESS_H

namespace eNetworks
{

namespace cservice
{

struct SqlChannelAccess
{
   public:
   	SqlChannelAccess(const unsigned int& id, const unsigned int& username_id, const unsigned int& channel_id, 
                         const unsigned short& level, const unsigned short& automode = 0) :
   	M_id(id), M_channel_id(channel_id), M_username_id(username_id), M_level(level), M_automode(0)
   	{
   	}

   	SqlChannelAccess() : M_id(0), M_username_id(0), M_channel_id(0), M_level(0)
   	{
   	}

   	enum AutoMode { AUTOMODE_NONE, AUTOMODE_OP, AUTOMODE_VOICE };

   	unsigned int getID() const { return M_id; }
   	unsigned int getUsernameID() const { return M_username_id; }
   	unsigned int getChannelID() const { return M_channel_id; }
   	unsigned short getLevel() const { return M_level; }
   	unsigned short getAutomode() const { return M_automode; }

   	void setID(const unsigned int& id)
   	{
   	   M_id = id;
   	}

   	void setUsernameID(const unsigned int& username_id)
   	{
   	   M_username_id = username_id;
   	}

   	void setChannelID(const unsigned int& channel_id)
   	{
   	   M_channel_id = channel_id;
   	}

   	void setLevel(const unsigned  short& level)
   	{
   	   M_level = level;
   	}

   	void setAutomode(const unsigned short& automode)
   	{
   	   M_automode = automode;
   	}

   	void update();
   	void Delete();

   private:
   	unsigned int M_id;
   	unsigned int M_username_id;
   	unsigned int M_channel_id;
   	unsigned short M_level;
   	unsigned short M_automode;
};

} // namespace eNetworks

} // namespace cservice

#endif // ELECTRONIC_NETWORKS__CSERVICE_SQLCHANNELACCESS_H
