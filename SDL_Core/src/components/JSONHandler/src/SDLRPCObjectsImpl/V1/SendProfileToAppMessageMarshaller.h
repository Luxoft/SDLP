#ifndef NSSMARTDEVICELINKRPC_SENDPROFILETOAPPMESSAGEMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPC_SENDPROFILETOAPPMESSAGEMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/SDLRPCObjects/V1/SendProfileToAppMessage.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jun 24 12:39:25 2013
  source stamp	Mon Jun 24 12:23:03 2013
  author	RC
*/

namespace NsSmartDeviceLinkRPC
{

  struct SendProfileToAppMessageMarshaller
  {
    static bool checkIntegrity(SendProfileToAppMessage& e);
    static bool checkIntegrityConst(const SendProfileToAppMessage& e);
  
    static bool fromString(const std::string& s,SendProfileToAppMessage& e);
    static const std::string toString(const SendProfileToAppMessage& e);
  
    static bool fromJSON(const Json::Value& s,SendProfileToAppMessage& e);
    static Json::Value toJSON(const SendProfileToAppMessage& e);
  };
}

#endif
