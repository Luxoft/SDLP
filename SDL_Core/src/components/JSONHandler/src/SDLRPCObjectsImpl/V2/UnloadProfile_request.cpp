#include "../include/JSONHandler/SDLRPCObjects/V2/UnloadProfile_request.h"
#include "UnloadProfile_requestMarshaller.h"
#include "../include/JSONHandler/SDLRPCObjects/V2/Marshaller.h"

#define PROTOCOL_VERSION	2


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPCV2;
UnloadProfile_request& UnloadProfile_request::operator =(const UnloadProfile_request& c)
{
  name= c.name ? new std::string(c.name[0]) : 0;

  return *this;}


UnloadProfile_request::~UnloadProfile_request(void)
{
  if(name)
    delete name;
}


UnloadProfile_request::UnloadProfile_request(const UnloadProfile_request& c)
{
  *this=c;
}


bool UnloadProfile_request::checkIntegrity(void)
{
  return UnloadProfile_requestMarshaller::checkIntegrity(*this);
}


UnloadProfile_request::UnloadProfile_request(void) : 
    NsSmartDeviceLinkRPC::SDLRPCRequest(PROTOCOL_VERSION),
    name(0)
{
}



bool UnloadProfile_request::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void UnloadProfile_request::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}




const std::string* UnloadProfile_request::get_name(void) const 
{
  return name;
}

