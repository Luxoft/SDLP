#ifndef NSSMARTDEVICELINKRPCV2_ONPROFILESTATECHANGEDMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPCV2_ONPROFILESTATECHANGEDMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/SDLRPCObjects/V2/OnProfileStateChanged.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

namespace NsSmartDeviceLinkRPCV2
{

  struct OnProfileStateChangedMarshaller
  {
    static bool checkIntegrity(OnProfileStateChanged& e);
    static bool checkIntegrityConst(const OnProfileStateChanged& e);
  
    static bool fromString(const std::string& s,OnProfileStateChanged& e);
    static const std::string toString(const OnProfileStateChanged& e);
  
    static bool fromJSON(const Json::Value& s,OnProfileStateChanged& e);
    static Json::Value toJSON(const OnProfileStateChanged& e);
  };
}

#endif
