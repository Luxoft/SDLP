#ifndef NSSMARTDEVICELINKRPC_MOBILEAPPSTATEMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPC_MOBILEAPPSTATEMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "PerfectHashTable.h"

#include "../include/JSONHandler/SDLRPCObjects/V1/MobileAppState.h"


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

//! marshalling class for MobileAppState

  class MobileAppStateMarshaller
  {
  public:
  
    static std::string toName(const MobileAppState& e) 	{ return getName(e.mInternal) ?: ""; }
  
    static bool fromName(MobileAppState& e,const std::string& s)
    { 
      return (e.mInternal=getIndex(s.c_str()))!=MobileAppState::INVALID_ENUM;
    }
  
    static bool checkIntegrity(MobileAppState& e)		{ return e.mInternal!=MobileAppState::INVALID_ENUM; } 
    static bool checkIntegrityConst(const MobileAppState& e)	{ return e.mInternal!=MobileAppState::INVALID_ENUM; } 
  
    static bool fromString(const std::string& s,MobileAppState& e);
    static const std::string toString(const MobileAppState& e);
  
    static bool fromJSON(const Json::Value& s,MobileAppState& e);
    static Json::Value toJSON(const MobileAppState& e);
  
    static const char* getName(MobileAppState::MobileAppStateInternal e)
    {
       return (e>=0 && e<3) ? mHashTable[e].name : NULL;
    }
  
    static const MobileAppState::MobileAppStateInternal getIndex(const char* s);
  
    static const PerfectHashTable mHashTable[3];
  };
  
}

#endif
