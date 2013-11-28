#include "../include/JSONHandler/SDLRPCObjects/V1/LoadProfile_request.h"
#include "LoadProfile_requestMarshaller.h"
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
LoadProfile_request& LoadProfile_request::operator =(const LoadProfile_request& c)
{
  name= c.name ? new std::string(c.name[0]) : 0;

  return *this;}


LoadProfile_request::~LoadProfile_request(void)
{
  if(name)
    delete name;
}


LoadProfile_request::LoadProfile_request(const LoadProfile_request& c)
{
  *this=c;
}


bool LoadProfile_request::checkIntegrity(void)
{
  return LoadProfile_requestMarshaller::checkIntegrity(*this);
}


LoadProfile_request::LoadProfile_request(void) : SDLRPCRequest(PROTOCOL_VERSION,Marshaller::METHOD_LOADPROFILE_REQUEST),
      name(0)
{
}



bool LoadProfile_request::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void LoadProfile_request::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}




const std::string* LoadProfile_request::get_name(void) const 
{
  return name;
}

