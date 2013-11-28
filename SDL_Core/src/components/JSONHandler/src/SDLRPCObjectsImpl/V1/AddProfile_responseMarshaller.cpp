#include "../include/JSONHandler/SDLRPCObjects/V1/AddProfile_response.h"
#include "ResultMarshaller.h"

#include "AddProfile_responseMarshaller.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPC;


bool AddProfile_responseMarshaller::checkIntegrity(AddProfile_response& s)
{
  return checkIntegrityConst(s);
}


bool AddProfile_responseMarshaller::fromString(const std::string& s,AddProfile_response& e)
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


const std::string AddProfile_responseMarshaller::toString(const AddProfile_response& e)
{
  Json::FastWriter writer;
  return checkIntegrityConst(e) ? writer.write(toJSON(e)) : "";
}


bool AddProfile_responseMarshaller::checkIntegrityConst(const AddProfile_response& s)
{
  if(!ResultMarshaller::checkIntegrityConst(s.resultCode))  return false;
  if(s.info && s.info->length()>1000)  return false;
  return true;
}

Json::Value AddProfile_responseMarshaller::toJSON(const AddProfile_response& e)
{
  Json::Value json(Json::objectValue);
  if(!checkIntegrityConst(e))
    return Json::Value(Json::nullValue);

  json["response"]=Json::Value(Json::objectValue);
  json["response"]["name"]=Json::Value("AddProfile");
  json["response"]["correlationID"]=Json::Value(e.getCorrelationID());

  Json::Value j=Json::Value(Json::objectValue);

  j["resultCode"]=ResultMarshaller::toJSON(e.resultCode);

  if(e.info)
    j["info"]=Json::Value(*e.info);

  json["response"]["parameters"]=j;
  return json;
}


bool AddProfile_responseMarshaller::fromJSON(const Json::Value& js,AddProfile_response& c)
{
  if(c.info)  delete c.info;
  c.info=0;

  try
  {
    if(!js.isObject())  return false;

    if(!js.isMember("response"))  return false;

    if(!js["response"].isObject())  return false;
    const Json::Value& j2=js["response"];

    if(!j2.isMember("name") || !j2["name"].isString() || j2["name"].asString().compare("AddProfile"))  return false;
    if(!j2.isMember("correlationID") || !j2["correlationID"].isInt())  return false;
    c.setCorrelationID(j2["correlationID"].asInt());

    if(!j2.isMember("parameters"))  return false;
    const Json::Value& json=j2["parameters"];
    if(!json.isObject())  return false;
    if(!json.isMember("resultCode"))  return false;
    {
      const Json::Value& j=json["resultCode"];
      if(!ResultMarshaller::fromJSON(j,c.resultCode))
        return false;
    }
    if(json.isMember("info"))
    {
      const Json::Value& j=json["info"];
      if(!j.isString())  return false;
      c.info=new std::string(j.asString());
    }

  }
  catch(...)
  {
    return false;
  }
  return checkIntegrity(c);
}

