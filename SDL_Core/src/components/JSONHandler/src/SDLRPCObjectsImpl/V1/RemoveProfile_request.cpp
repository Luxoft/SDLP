#include "../include/JSONHandler/SDLRPCObjects/V1/RemoveProfile_request.h"
#include "RemoveProfile_requestMarshaller.h"
#include "../include/JSONHandler/SDLRPCObjects/V1/Marshaller.h"

#define PROTOCOL_VERSION	1


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPC;
RemoveProfile_request& RemoveProfile_request::operator =(const RemoveProfile_request& c)
{
  name= c.name ? new std::string(c.name[0]) : 0;

  return *this;}


RemoveProfile_request::~RemoveProfile_request(void)
{
  if(name)
    delete name;
}


RemoveProfile_request::RemoveProfile_request(const RemoveProfile_request& c)
{
  *this=c;
}


bool RemoveProfile_request::checkIntegrity(void)
{
  return RemoveProfile_requestMarshaller::checkIntegrity(*this);
}


RemoveProfile_request::RemoveProfile_request(void) : SDLRPCRequest(PROTOCOL_VERSION,Marshaller::METHOD_REMOVEPROFILE_REQUEST),
      name(0)
{
}



bool RemoveProfile_request::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void RemoveProfile_request::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}




const std::string* RemoveProfile_request::get_name(void) const 
{
  return name;
}

