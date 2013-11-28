#include "../include/JSONHandler/SDLRPCObjects/V2/AddProfile_request.h"
#include "AddProfile_requestMarshaller.h"
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
AddProfile_request& AddProfile_request::operator =(const AddProfile_request& c)
{
  name= c.name ? new std::string(c.name[0]) : 0;
  profileBinary= c.profileBinary ? new std::string(c.profileBinary[0]) : 0;

  return *this;}


AddProfile_request::~AddProfile_request(void)
{
  if(name)
    delete name;
  if(profileBinary)
    delete profileBinary;
}


AddProfile_request::AddProfile_request(const AddProfile_request& c)
{
  *this=c;
}


bool AddProfile_request::checkIntegrity(void)
{
  return AddProfile_requestMarshaller::checkIntegrity(*this);
}


AddProfile_request::AddProfile_request(void) : 
    NsSmartDeviceLinkRPC::SDLRPCRequest(PROTOCOL_VERSION),
    name(0),
    profileBinary(0)
{
}



bool AddProfile_request::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void AddProfile_request::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}

bool AddProfile_request::set_profileBinary(const std::string& profileBinary_)
{
  delete profileBinary;
  profileBinary=0;

  profileBinary=new std::string(profileBinary_);
  return true;
}

void AddProfile_request::reset_profileBinary(void)
{
  if(profileBinary)
    delete profileBinary;
  profileBinary=0;
}




const std::string* AddProfile_request::get_name(void) const 
{
  return name;
}

const std::string* AddProfile_request::get_profileBinary(void) const 
{
  return profileBinary;
}

