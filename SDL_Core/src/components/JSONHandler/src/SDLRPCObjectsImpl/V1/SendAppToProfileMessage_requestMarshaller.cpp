#include "../include/JSONHandler/SDLRPCObjects/V1/SendAppToProfileMessage_request.h"


#include "SendAppToProfileMessage_requestMarshaller.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPC;


bool SendAppToProfileMessage_requestMarshaller::checkIntegrity(SendAppToProfileMessage_request& s)
{
  return checkIntegrityConst(s);
}


bool SendAppToProfileMessage_requestMarshaller::fromString(const std::string& s,SendAppToProfileMessage_request& e)
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


const std::string SendAppToProfileMessage_requestMarshaller::toString(const SendAppToProfileMessage_request& e)
{
  Json::FastWriter writer;
  return checkIntegrityConst(e) ? writer.write(toJSON(e)) : "";
}


bool SendAppToProfileMessage_requestMarshaller::checkIntegrityConst(const SendAppToProfileMessage_request& s)
{
  if(s.name && s.name->length()>1000)  return false;
  return true;
}

Json::Value SendAppToProfileMessage_requestMarshaller::toJSON(const SendAppToProfileMessage_request& e)
{
  Json::Value json(Json::objectValue);
  if(!checkIntegrityConst(e))
    return Json::Value(Json::nullValue);

  json["request"]=Json::Value(Json::objectValue);
  json["request"]["name"]=Json::Value("SendAppToProfileMessage");
  json["request"]["correlationID"]=Json::Value(e.getCorrelationID());

  Json::Value j=Json::Value(Json::objectValue);

  if(e.profileData)
    j["profileData"]=Json::Value(*e.profileData);

  if(e.name)
    j["name"]=Json::Value(*e.name);

  json["request"]["parameters"]=j;
  return json;
}


bool SendAppToProfileMessage_requestMarshaller::fromJSON(const Json::Value& js,SendAppToProfileMessage_request& c)
{
  if(c.profileData)  delete c.profileData;
  c.profileData=0;

  if(c.name)  delete c.name;
  c.name=0;

  try
  {
    if(!js.isObject())  return false;

    if(!js.isMember("request"))  return false;

    if(!js["request"].isObject())  return false;
    const Json::Value& j2=js["request"];

    if(!j2.isMember("name") || !j2["name"].isString() || j2["name"].asString().compare("SendAppToProfileMessage"))  return false;
    if(!j2.isMember("correlationID") || !j2["correlationID"].isInt())  return false;
    c.setCorrelationID(j2["correlationID"].asInt());

    if(!j2.isMember("parameters"))  return false;
    const Json::Value& json=j2["parameters"];
    if(!json.isObject())  return false;
    if(json.isMember("profileData"))
    {
      const Json::Value& j=json["profileData"];
      if(!j.isString())  return false;
      c.profileData=new std::string(j.asString());
    }
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

