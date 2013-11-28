#include "../include/JSONHandler/SDLRPCObjects/V1/SendProfileToAppMessage.h"


#include "SendProfileToAppMessageMarshaller.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jun 24 12:39:25 2013
  source stamp	Mon Jun 24 12:23:03 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPC;


bool SendProfileToAppMessageMarshaller::checkIntegrity(SendProfileToAppMessage& s)
{
  return checkIntegrityConst(s);
}


bool SendProfileToAppMessageMarshaller::fromString(const std::string& s,SendProfileToAppMessage& e)
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


const std::string SendProfileToAppMessageMarshaller::toString(const SendProfileToAppMessage& e)
{
  Json::FastWriter writer;
  return checkIntegrityConst(e) ? writer.write(toJSON(e)) : "";
}


bool SendProfileToAppMessageMarshaller::checkIntegrityConst(const SendProfileToAppMessage& s)
{
  if(s.name && s.name->length()>1000)  return false;
  return true;
}

Json::Value SendProfileToAppMessageMarshaller::toJSON(const SendProfileToAppMessage& e)
{
  Json::Value json(Json::objectValue);
  if(!checkIntegrityConst(e))
    return Json::Value(Json::nullValue);

  json["notification"]=Json::Value(Json::objectValue);
  json["notification"]["name"]=Json::Value("SendProfileToAppMessage");

  Json::Value j=Json::Value(Json::objectValue);

  if(e.name)
    j["name"]=Json::Value(*e.name);

  j["data"]=Json::Value(e.data);

  json["notification"]["parameters"]=j;
  return json;
}


bool SendProfileToAppMessageMarshaller::fromJSON(const Json::Value& js,SendProfileToAppMessage& c)
{
  if(c.name)  delete c.name;
  c.name=0;

  try
  {
    if(!js.isObject())  return false;

    if(!js.isMember("notification"))  return false;

    if(!js["notification"].isObject())  return false;
    const Json::Value& j2=js["notification"];

    if(!j2.isMember("name") || !j2["name"].isString() || j2["name"].asString().compare("SendProfileToAppMessage"))  return false;

    if(!j2.isMember("parameters"))  return false;
    const Json::Value& json=j2["parameters"];
    if(!json.isObject())  return false;
    if(json.isMember("name"))
    {
      const Json::Value& j=json["name"];
      if(!j.isString())  return false;
      c.name=new std::string(j.asString());
    }
    if(!json.isMember("data"))  return false;
    {
      const Json::Value& j=json["data"];
      if(!j.isString())  return false;
      c.data=j.asString();
    }

  }
  catch(...)
  {
    return false;
  }
  return checkIntegrity(c);
}

