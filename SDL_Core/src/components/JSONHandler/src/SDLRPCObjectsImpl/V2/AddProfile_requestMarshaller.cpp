#include "../include/JSONHandler/SDLRPCObjects/V2/AddProfile_request.h"


#include "AddProfile_requestMarshaller.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPCV2;


bool AddProfile_requestMarshaller::checkIntegrity(AddProfile_request& s)
{
  return checkIntegrityConst(s);
}


bool AddProfile_requestMarshaller::fromString(const std::string& s,AddProfile_request& e)
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


const std::string AddProfile_requestMarshaller::toString(const AddProfile_request& e)
{
  Json::FastWriter writer;
  return checkIntegrityConst(e) ? writer.write(toJSON(e)) : "";
}


bool AddProfile_requestMarshaller::checkIntegrityConst(const AddProfile_request& s)
{
  if(s.name && s.name->length()>1000)  return false;
  return true;
}

Json::Value AddProfile_requestMarshaller::toJSON(const AddProfile_request& e)
{
  Json::Value json(Json::objectValue);
  if(!checkIntegrityConst(e))
    return Json::Value(Json::nullValue);
  if(e.name)
    json["name"]=Json::Value(*e.name);

  if(e.profileBinary)
    json["profileBinary"]=Json::Value(*e.profileBinary);

  return json;
}


bool AddProfile_requestMarshaller::fromJSON(const Json::Value& js,AddProfile_request& c)
{
  if(c.name)  delete c.name;
  c.name=0;

  if(c.profileBinary)  delete c.profileBinary;
  c.profileBinary=0;

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
    if(json.isMember("profileBinary"))
    {
      const Json::Value& j=json["profileBinary"];
      if(!j.isString())  return false;
      c.profileBinary=new std::string(j.asString());
    }

  }
  catch(...)
  {
    return false;
  }
  return checkIntegrity(c);
}

