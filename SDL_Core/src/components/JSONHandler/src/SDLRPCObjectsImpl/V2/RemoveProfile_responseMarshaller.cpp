#include "../include/JSONHandler/SDLRPCObjects/V2/RemoveProfile_response.h"
#include "ResultMarshaller.h"

#include "RemoveProfile_responseMarshaller.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPCV2;


bool RemoveProfile_responseMarshaller::checkIntegrity(RemoveProfile_response& s)
{
  return checkIntegrityConst(s);
}


bool RemoveProfile_responseMarshaller::fromString(const std::string& s,RemoveProfile_response& e)
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


const std::string RemoveProfile_responseMarshaller::toString(const RemoveProfile_response& e)
{
  Json::FastWriter writer;
  return checkIntegrityConst(e) ? writer.write(toJSON(e)) : "";
}


bool RemoveProfile_responseMarshaller::checkIntegrityConst(const RemoveProfile_response& s)
{
  if(!ResultMarshaller::checkIntegrityConst(s.resultCode))  return false;
  if(s.info && s.info->length()>1000)  return false;
  return true;
}

Json::Value RemoveProfile_responseMarshaller::toJSON(const RemoveProfile_response& e)
{
  Json::Value json(Json::objectValue);
  if(!checkIntegrityConst(e))
    return Json::Value(Json::nullValue);

  json["resultCode"]=ResultMarshaller::toJSON(e.resultCode);

  if(e.info)
    json["info"]=Json::Value(*e.info);

  return json;
}


bool RemoveProfile_responseMarshaller::fromJSON(const Json::Value& js,RemoveProfile_response& c)
{
  if(c.info)  delete c.info;
  c.info=0;

  try
  {
    if(!js.isObject())  return false;

    if(!js.isMember("parameters"))  return false;
    const Json::Value& json=js["parameters"];
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

