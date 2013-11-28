#include "../include/JSONHandler/SDLRPCObjects/V1/OnUnloadProfile.h"
#include "ActionPerformerMarshaller.h"

#include "OnUnloadProfileMarshaller.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jun 24 12:39:25 2013
  source stamp	Mon Jun 24 12:23:03 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPC;


bool OnUnloadProfileMarshaller::checkIntegrity(OnUnloadProfile& s)
{
  return checkIntegrityConst(s);
}


bool OnUnloadProfileMarshaller::fromString(const std::string& s,OnUnloadProfile& e)
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


const std::string OnUnloadProfileMarshaller::toString(const OnUnloadProfile& e)
{
  Json::FastWriter writer;
  return checkIntegrityConst(e) ? writer.write(toJSON(e)) : "";
}


bool OnUnloadProfileMarshaller::checkIntegrityConst(const OnUnloadProfile& s)
{
  if(s.name && s.name->length()>1000)  return false;
  if(!ActionPerformerMarshaller::checkIntegrityConst(s.performer))  return false;
  return true;
}

Json::Value OnUnloadProfileMarshaller::toJSON(const OnUnloadProfile& e)
{
  Json::Value json(Json::objectValue);
  if(!checkIntegrityConst(e))
    return Json::Value(Json::nullValue);

  json["notification"]=Json::Value(Json::objectValue);
  json["notification"]["name"]=Json::Value("OnUnloadProfile");

  Json::Value j=Json::Value(Json::objectValue);

  if(e.name)
    j["name"]=Json::Value(*e.name);

  j["performer"]=ActionPerformerMarshaller::toJSON(e.performer);

  json["notification"]["parameters"]=j;
  return json;
}


bool OnUnloadProfileMarshaller::fromJSON(const Json::Value& js,OnUnloadProfile& c)
{
  if(c.name)  delete c.name;
  c.name=0;

  try
  {
    if(!js.isObject())  return false;

    if(!js.isMember("notification"))  return false;

    if(!js["notification"].isObject())  return false;
    const Json::Value& j2=js["notification"];

    if(!j2.isMember("name") || !j2["name"].isString() || j2["name"].asString().compare("OnUnloadProfile"))  return false;

    if(!j2.isMember("parameters"))  return false;
    const Json::Value& json=j2["parameters"];
    if(!json.isObject())  return false;
    if(json.isMember("name"))
    {
      const Json::Value& j=json["name"];
      if(!j.isString())  return false;
      c.name=new std::string(j.asString());
    }
    if(!json.isMember("performer"))  return false;
    {
      const Json::Value& j=json["performer"];
      if(!ActionPerformerMarshaller::fromJSON(j,c.performer))
        return false;
    }

  }
  catch(...)
  {
    return false;
  }
  return checkIntegrity(c);
}

