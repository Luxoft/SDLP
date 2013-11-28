#ifndef NSSMARTDEVICELINKRPC_ONPROFILETOAPPMESSAGEMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPC_ONPROFILETOAPPMESSAGEMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/SDLRPCObjects/V1/OnProfileToAppMessage.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

namespace NsSmartDeviceLinkRPC
{

  struct OnProfileToAppMessageMarshaller
  {
    static bool checkIntegrity(OnProfileToAppMessage& e);
    static bool checkIntegrityConst(const OnProfileToAppMessage& e);
  
    static bool fromString(const std::string& s,OnProfileToAppMessage& e);
    static const std::string toString(const OnProfileToAppMessage& e);
  
    static bool fromJSON(const Json::Value& s,OnProfileToAppMessage& e);
    static Json::Value toJSON(const OnProfileToAppMessage& e);
  };
}

#endif
