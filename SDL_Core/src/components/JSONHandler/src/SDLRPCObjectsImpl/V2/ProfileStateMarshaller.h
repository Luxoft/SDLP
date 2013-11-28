#ifndef NSSMARTDEVICELINKRPCV2_PROFILESTATEMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPCV2_PROFILESTATEMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "PerfectHashTable.h"

#include "../include/JSONHandler/SDLRPCObjects/V2/ProfileState.h"


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

//! marshalling class for ProfileState

  class ProfileStateMarshaller
  {
  public:
  
    static std::string toName(const ProfileState& e) 	{ return getName(e.mInternal) ?: ""; }
  
    static bool fromName(ProfileState& e,const std::string& s)
    { 
      return (e.mInternal=getIndex(s.c_str()))!=ProfileState::INVALID_ENUM;
    }
  
    static bool checkIntegrity(ProfileState& e)	{ 
        return e.mInternal!=ProfileState::INVALID_ENUM; 
    } 
    static bool checkIntegrityConst(const ProfileState& e) {
        return e.mInternal!=ProfileState::INVALID_ENUM;
    } 
  
    static bool fromString(const std::string& s,ProfileState& e);
    static const std::string toString(const ProfileState& e);
  
    static bool fromJSON(const Json::Value& s,ProfileState& e);
    static Json::Value toJSON(const ProfileState& e);
  
    static const char* getName(ProfileState::ProfileStateInternal e)
    {
       return (e>=0 && e<3) ? mHashTable[e].name : NULL;
    }
  
    static const ProfileState::ProfileStateInternal getIndex(const char* s);
  
    static const PerfectHashTable mHashTable[3];
  };
  
}

#endif
