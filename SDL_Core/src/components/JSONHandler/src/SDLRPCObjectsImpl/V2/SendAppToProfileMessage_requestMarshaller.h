#ifndef NSSMARTDEVICELINKRPCV2_SENDAPPTOPROFILEMESSAGE_REQUESTMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPCV2_SENDAPPTOPROFILEMESSAGE_REQUESTMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/SDLRPCObjects/V2/SendAppToProfileMessage_request.h"


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

  struct SendAppToProfileMessage_requestMarshaller
  {
    static bool checkIntegrity(SendAppToProfileMessage_request& e);
    static bool checkIntegrityConst(const SendAppToProfileMessage_request& e);
  
    static bool fromString(const std::string& s,SendAppToProfileMessage_request& e);
    static const std::string toString(const SendAppToProfileMessage_request& e);
  
    static bool fromJSON(const Json::Value& s,SendAppToProfileMessage_request& e);
    static Json::Value toJSON(const SendAppToProfileMessage_request& e);
  };
}

#endif
