#include <cstring>
#include "../include/JSONHandler/SDLRPCObjects/V2/ProfileState.h"
#include "ProfileStateMarshaller.h"

namespace NsSmartDeviceLinkRPCV2
{
  #include "ProfileStateMarshaller.inc"
}


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPCV2;


const ProfileState::ProfileStateInternal ProfileStateMarshaller::getIndex(const char* s)
{
  if(!s)
    return ProfileState::INVALID_ENUM;
  const struct PerfectHashTable* p=ProfileState_intHash::getPointer(s,strlen(s));
  return p ? static_cast<ProfileState::ProfileStateInternal>(p->idx) : ProfileState::INVALID_ENUM;
}


bool ProfileStateMarshaller::fromJSON(const Json::Value& s,ProfileState& e)
{
  e.mInternal=ProfileState::INVALID_ENUM;
  if(!s.isString())
    return false;

  e.mInternal=getIndex(s.asString().c_str());
  return (e.mInternal!=ProfileState::INVALID_ENUM);
}


Json::Value ProfileStateMarshaller::toJSON(const ProfileState& e)
{
  if(e.mInternal==ProfileState::INVALID_ENUM) 
    return Json::Value(Json::nullValue);
  const char* s=getName(e.mInternal);
  return s ? Json::Value(s) : Json::Value(Json::nullValue);
}


bool ProfileStateMarshaller::fromString(const std::string& s,ProfileState& e)
{
  e.mInternal=ProfileState::INVALID_ENUM;
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

const std::string ProfileStateMarshaller::toString(const ProfileState& e)
{
  Json::FastWriter writer;
  return e.mInternal==ProfileState::INVALID_ENUM ? "" : writer.write(toJSON(e));

}

const PerfectHashTable ProfileStateMarshaller::mHashTable[3]=
{
  {"FOREGROUND",0},
  {"LIMITED",1},
  {"BACKGROUND",2}
};
