#include "Client.h"
#include "Channel.h"

namespace eNetworks
{

bool Client::AddChannel(Channel *aChannelPtr)
{
   if (aChannelPtr == NULL)
    return false;

   return ChannelMap.insert(ChannelMapType::value_type(aChannelPtr->GetName(), aChannelPtr)).second;
}

bool Client::DelChannel(Channel *aChannelPtr)
{
   if (aChannelPtr == NULL)
    return false;

   if (ChannelMap.erase(aChannelPtr->GetName()) != 1)
    return false;
   // else
   return true;
}

Client *LocalClient;

} // namespace eNetworks
