#ifndef NSSMARTDEVICELINKRPC_ONUNLOADPROFILEMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPC_ONUNLOADPROFILEMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/SDLRPCObjects/V1/OnUnloadProfile.h"


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

  struct OnUnloadProfileMarshaller
  {
    static bool checkIntegrity(OnUnloadProfile& e);
    static bool checkIntegrityConst(const OnUnloadProfile& e);
  
    static bool fromString(const std::string& s,OnUnloadProfile& e);
    static const std::string toString(const OnUnloadProfile& e);
  
    static bool fromJSON(const Json::Value& s,OnUnloadProfile& e);
    static Json::Value toJSON(const OnUnloadProfile& e);
  };
}

#endif
