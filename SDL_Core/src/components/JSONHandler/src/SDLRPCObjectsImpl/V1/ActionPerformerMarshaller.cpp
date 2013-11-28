#include <cstring>
#include "../include/JSONHandler/SDLRPCObjects/V1/ActionPerformer.h"
#include "ActionPerformerMarshaller.h"
//#include "ActionPerformerMarshaller.inc"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPC;


const ActionPerformer::ActionPerformerInternal ActionPerformerMarshaller::getIndex(const char* s)
{
  if(!s)
    return ActionPerformer::INVALID_ENUM;
  const struct PerfectHashTable* p=NULL/*ActionPerformer_intHash::getPointer(s,strlen(s))*/;
  return p ? static_cast<ActionPerformer::ActionPerformerInternal>(p->idx) : ActionPerformer::INVALID_ENUM;
}


bool ActionPerformerMarshaller::fromJSON(const Json::Value& s,ActionPerformer& e)
{
  e.mInternal=ActionPerformer::INVALID_ENUM;
  if(!s.isString())
    return false;

  e.mInternal=getIndex(s.asString().c_str());
  return (e.mInternal!=ActionPerformer::INVALID_ENUM);
}


Json::Value ActionPerformerMarshaller::toJSON(const ActionPerformer& e)
{
  if(e.mInternal==ActionPerformer::INVALID_ENUM) 
    return Json::Value(Json::nullValue);
  const char* s=getName(e.mInternal);
  return s ? Json::Value(s) : Json::Value(Json::nullValue);
}


bool ActionPerformerMarshaller::fromString(const std::string& s,ActionPerformer& e)
{
  e.mInternal=ActionPerformer::INVALID_ENUM;
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

const std::string ActionPerformerMarshaller::toString(const ActionPerformer& e)
{
  Json::FastWriter writer;
  return e.mInternal==ActionPerformer::INVALID_ENUM ? "" : writer.write(toJSON(e));

}

const PerfectHashTable ActionPerformerMarshaller::mHashTable[2]=
{
  {"AP_SYSTEM",0},
  {"AP_USER",1}
};
