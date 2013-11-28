#ifndef NSSMARTDEVICELINKRPC_REMOVEPROFILE_REQUESTMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPC_REMOVEPROFILE_REQUESTMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/SDLRPCObjects/V1/RemoveProfile_request.h"


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

  struct RemoveProfile_requestMarshaller
  {
    static bool checkIntegrity(RemoveProfile_request& e);
    static bool checkIntegrityConst(const RemoveProfile_request& e);
  
    static bool fromString(const std::string& s,RemoveProfile_request& e);
    static const std::string toString(const RemoveProfile_request& e);
  
    static bool fromJSON(const Json::Value& s,RemoveProfile_request& e);
    static Json::Value toJSON(const RemoveProfile_request& e);
  };
}

#endif
