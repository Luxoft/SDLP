#ifndef NSSMARTDEVICELINKRPC_ADDPROFILE_REQUESTMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPC_ADDPROFILE_REQUESTMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/SDLRPCObjects/V1/AddProfile_request.h"


/*
  interface Ford Sync RAPI
  version 1.2
  date    2011-05-17
  generated at  Mon Jul  1 13:13:32 2013
  source stamp  Sun Jun 30 21:55:31 2013
  author  RC
*/

namespace NsSmartDeviceLinkRPC
{

  struct AddProfile_requestMarshaller
  {
    static bool checkIntegrity(AddProfile_request& e);
    static bool checkIntegrityConst(const AddProfile_request& e);
  
    static bool fromString(const std::string& s,AddProfile_request& e);
    static const std::string toString(const AddProfile_request& e);
  
    static bool fromJSON(const Json::Value& s,AddProfile_request& e);
    static Json::Value toJSON(const AddProfile_request& e);
  };
}

#endif
