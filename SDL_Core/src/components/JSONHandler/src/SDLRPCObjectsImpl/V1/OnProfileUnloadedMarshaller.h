#ifndef NSSMARTDEVICELINKRPC_ONPROFILEUNLOADEDMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPC_ONPROFILEUNLOADEDMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/SDLRPCObjects/V1/OnProfileUnloaded.h"


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

  struct OnProfileUnloadedMarshaller
  {
    static bool checkIntegrity(OnProfileUnloaded& e);
    static bool checkIntegrityConst(const OnProfileUnloaded& e);
  
    static bool fromString(const std::string& s,OnProfileUnloaded& e);
    static const std::string toString(const OnProfileUnloaded& e);
  
    static bool fromJSON(const Json::Value& s,OnProfileUnloaded& e);
    static Json::Value toJSON(const OnProfileUnloaded& e);
  };
}

#endif
