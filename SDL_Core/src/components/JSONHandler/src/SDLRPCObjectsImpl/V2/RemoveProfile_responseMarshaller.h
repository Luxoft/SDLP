#ifndef NSSMARTDEVICELINKRPCV2_REMOVEPROFILE_RESPONSEMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPCV2_REMOVEPROFILE_RESPONSEMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/SDLRPCObjects/V2/RemoveProfile_response.h"


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

  struct RemoveProfile_responseMarshaller
  {
    static bool checkIntegrity(RemoveProfile_response& e);
    static bool checkIntegrityConst(const RemoveProfile_response& e);
  
    static bool fromString(const std::string& s,RemoveProfile_response& e);
    static const std::string toString(const RemoveProfile_response& e);
  
    static bool fromJSON(const Json::Value& s,RemoveProfile_response& e);
    static Json::Value toJSON(const RemoveProfile_response& e);
  };
}

#endif
