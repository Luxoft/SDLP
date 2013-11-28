#include "../include/JSONHandler/SDLRPCObjects/V2/OnProfileUnloaded.h"
#include "ActionPerformerMarshaller.h"

#include "OnProfileUnloadedMarshaller.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPCV2;


bool OnProfileUnloadedMarshaller::checkIntegrity(OnProfileUnloaded& s)
{
  return checkIntegrityConst(s);
}


bool OnProfileUnloadedMarshaller::fromString(const std::string& s,OnProfileUnloaded& e)
{
  try
  {
    Json::Reader reader;
    Json::Value json;
    if(!reader.parse(s,json,false))  return false;
    if(!fromJSON(json,e))  return false;
  }
  catch(...)
  {
    return false;
  }
  return true;
}


const std::string OnProfileUnloadedMarshaller::toString(const OnProfileUnloaded& e)
{
  Json::FastWriter writer;
  return checkIntegrityConst(e) ? writer.write(toJSON(e)) : "";
}


bool OnProfileUnloadedMarshaller::checkIntegrityConst(const OnProfileUnloaded& s)
{
  return !(s.name && s.name->length()>1000);
}

Json::Value OnProfileUnloadedMarshaller::toJSON(const OnProfileUnloaded& e)
{
  Json::Value json(Json::objectValue);
  if(!checkIntegrityConst(e))
  {
    return Json::Value(Json::nullValue);
  }

  if(e.name)
    json["name"]=Json::Value(*e.name);

  return json;
}


bool OnProfileUnloadedMarshaller::fromJSON(const Json::Value& js,OnProfileUnloaded& c)
{
  if(c.name)  delete c.name;
  c.name=0;

  try
  {
    if(!js.isObject())  return false;

    if(!js.isMember("parameters"))  return false;
    const Json::Value& json=js["parameters"];
    if(!json.isObject())  return false;
    if(json.isMember("name"))
    {
      const Json::Value& j=json["name"];
      if(!j.isString())  return false;
      c.name=new std::string(j.asString());
    }

  }
  catch(...)
  {
    return false;
  }
  return checkIntegrity(c);
}

