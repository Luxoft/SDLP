#include "../include/JSONHandler/SDLRPCObjects/V1/OnProfileStateChanged.h"
#include "ProfileStateMarshaller.h"

#include "OnProfileStateChangedMarshaller.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPC;


bool OnProfileStateChangedMarshaller::checkIntegrity(OnProfileStateChanged& s)
{
  return checkIntegrityConst(s);
}


bool OnProfileStateChangedMarshaller::fromString(const std::string& s,OnProfileStateChanged& e)
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


const std::string OnProfileStateChangedMarshaller::toString(const OnProfileStateChanged& e)
{
  Json::FastWriter writer;
  return checkIntegrityConst(e) ? writer.write(toJSON(e)) : "";
}


bool OnProfileStateChangedMarshaller::checkIntegrityConst(const OnProfileStateChanged& s)
{
  if(s.name && s.name->length()>1000)  return false;
  if(!ProfileStateMarshaller::checkIntegrityConst(s.state))  return false;
  return true;
}

Json::Value OnProfileStateChangedMarshaller::toJSON(const OnProfileStateChanged& e)
{
  Json::Value json(Json::objectValue);
  if(!checkIntegrityConst(e))
    return Json::Value(Json::nullValue);

  json["notification"]=Json::Value(Json::objectValue);
  json["notification"]["name"]=Json::Value("OnProfileStateChanged");

  Json::Value j=Json::Value(Json::objectValue);

  if(e.name)
    j["name"]=Json::Value(*e.name);

  j["state"]=ProfileStateMarshaller::toJSON(e.state);

  json["notification"]["parameters"]=j;
  return json;
}


bool OnProfileStateChangedMarshaller::fromJSON(const Json::Value& js,OnProfileStateChanged& c)
{
  if(c.name)  delete c.name;
  c.name=0;

  try
  {
    if(!js.isObject())  return false;

    if(!js.isMember("notification"))  return false;

    if(!js["notification"].isObject())  return false;
    const Json::Value& j2=js["notification"];

    if(!j2.isMember("name") || !j2["name"].isString() || j2["name"].asString().compare("OnProfileStateChanged"))  return false;

    if(!j2.isMember("parameters"))  return false;
    const Json::Value& json=j2["parameters"];
    if(!json.isObject())  return false;
    if(json.isMember("name"))
    {
      const Json::Value& j=json["name"];
      if(!j.isString())  return false;
      c.name=new std::string(j.asString());
    }
    if(!json.isMember("state"))  return false;
    {
      const Json::Value& j=json["state"];      
      if(!ProfileStateMarshaller::fromJSON(j,c.state))
      return false;
    }

  }
  catch(...)
  {
    return false;
  }
  return checkIntegrity(c);
}

