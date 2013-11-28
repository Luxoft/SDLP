#include <cstring>
#include "../include/JSONHandler/SDLRPCObjects/V1/MobileAppState.h"
#include "MobileAppStateMarshaller.h"

namespace NsSmartDeviceLinkRPC {
  #include "MobileAppStateMarshaller.inc"
}


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPC;


const MobileAppState::MobileAppStateInternal MobileAppStateMarshaller::getIndex(const char* s)
{
  if(!s)
    return MobileAppState::INVALID_ENUM;
  const struct PerfectHashTable* p=MobileAppState_intHash::getPointer(s,strlen(s));
  return p ? static_cast<MobileAppState::MobileAppStateInternal>(p->idx) : MobileAppState::INVALID_ENUM;
}


bool MobileAppStateMarshaller::fromJSON(const Json::Value& s,MobileAppState& e)
{
  e.mInternal=MobileAppState::INVALID_ENUM;
  if(!s.isString())
    return false;

  e.mInternal=getIndex(s.asString().c_str());
  return (e.mInternal!=MobileAppState::INVALID_ENUM);
}


Json::Value MobileAppStateMarshaller::toJSON(const MobileAppState& e)
{
  if(e.mInternal==MobileAppState::INVALID_ENUM) 
    return Json::Value(Json::nullValue);
  const char* s=getName(e.mInternal);
  return s ? Json::Value(s) : Json::Value(Json::nullValue);
}


bool MobileAppStateMarshaller::fromString(const std::string& s,MobileAppState& e)
{
  e.mInternal=MobileAppState::INVALID_ENUM;
  try
  {
    Json::Reader reader;
    Json::Value json;
    if(!reader.parse(s,json,false))  return false;
    if(fromJSON(json,e))  return true;
  }
  catch(...)
  {
    return false;
  }
  return false;
}

const std::string MobileAppStateMarshaller::toString(const MobileAppState& e)
{
  Json::FastWriter writer;
  return e.mInternal==MobileAppState::INVALID_ENUM ? "" : writer.write(toJSON(e));

}

const PerfectHashTable MobileAppStateMarshaller::mHashTable[3]=
{
  {"MOBILE_APP_FOREGROUND",0},
  {"MOBILE_APP_BACKGROUND",1},
  {"MOBILE_APP_LOCK_SCREEN",2}
};
