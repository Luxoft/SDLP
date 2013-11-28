#ifndef NSSMARTDEVICELINKRPC_ACTIONPERFORMERMARSHALLER_INCLUDE
#define NSSMARTDEVICELINKRPC_ACTIONPERFORMERMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "PerfectHashTable.h"

#include "../include/JSONHandler/SDLRPCObjects/V1/ActionPerformer.h"


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

//! marshalling class for ActionPerformer

  class ActionPerformerMarshaller
  {
  public:
  
    static std::string toName(const ActionPerformer& e) 	{ return getName(e.mInternal) ?: ""; }
  
    static bool fromName(ActionPerformer& e,const std::string& s)
    { 
      return (e.mInternal=getIndex(s.c_str()))!=ActionPerformer::INVALID_ENUM;
    }
  
    static bool checkIntegrity(ActionPerformer& e)		{ return e.mInternal!=ActionPerformer::INVALID_ENUM; } 
    static bool checkIntegrityConst(const ActionPerformer& e)	{ return e.mInternal!=ActionPerformer::INVALID_ENUM; } 
  
    static bool fromString(const std::string& s,ActionPerformer& e);
    static const std::string toString(const ActionPerformer& e);
  
    static bool fromJSON(const Json::Value& s,ActionPerformer& e);
    static Json::Value toJSON(const ActionPerformer& e);
  
    static const char* getName(ActionPerformer::ActionPerformerInternal e)
    {
       return (e>=0 && e<2) ? mHashTable[e].name : NULL;
    }
  
    static const ActionPerformer::ActionPerformerInternal getIndex(const char* s);
  
    static const PerfectHashTable mHashTable[2];
  };
  
}

#endif
