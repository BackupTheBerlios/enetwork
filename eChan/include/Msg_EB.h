#ifndef ELECTRONIC_NETWORKS__MSG_EB_H
#define ELECTRONIC_NETWORKS__MSG_EB_H

#include <string>

#include "Msg.h"

namespace eNetworks
{

// -------------------------------------------------------------------------------
//                    EB Token. (End of burst)
// -------------------------------------------------------------------------------
class Msg_EB : public Msg
{
   public:
        Msg_EB(const std::string &aCommand, const std::string &aToken) : Msg(aCommand, aToken) {}

        virtual ~Msg_EB() {}
        virtual void Parser();
};

} // namespace eNetworks

#endif // ELECTRONIC_NETWORKS__MSG_EB_H

