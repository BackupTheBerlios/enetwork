#ifndef ELECTRONIC_NETWORKS__MSG_G_H
#define ELECTRONIC_NETWORKS__MSG_G_H

#include <string>

#include "Msg.h"

namespace eNetworks
{

// -------------------------------------------------------------------------------
//                    G Token. (A server Pinging us)
// -------------------------------------------------------------------------------
class Msg_G : public Msg
{
   public:
        Msg_G(const std::string &aCommand, const std::string &aToken) : Msg(aCommand, aToken) {}

        virtual ~Msg_G() {}
        virtual void Parser();
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__MSG_G_H
