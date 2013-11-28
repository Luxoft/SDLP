#include "../include/JSONHandler/SDLRPCObjects/V1/SendAppToProfileMessage_request.h"
#include "SendAppToProfileMessage_requestMarshaller.h"
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
SendAppToProfileMessage_request& SendAppToProfileMessage_request::operator =(const SendAppToProfileMessage_request& c)
{
  profileData= c.profileData ? new std::string(c.profileData[0]) : 0;
  name= c.name ? new std::string(c.name[0]) : 0;

  return *this;}


SendAppToProfileMessage_request::~SendAppToProfileMessage_request(void)
{
  if(profileData)
    delete profileData;
  if(name)
    delete name;
}


SendAppToProfileMessage_request::SendAppToProfileMessage_request(const SendAppToProfileMessage_request& c)
{
  *this=c;
}


bool SendAppToProfileMessage_request::checkIntegrity(void)
{
  return SendAppToProfileMessage_requestMarshaller::checkIntegrity(*this);
}


SendAppToProfileMessage_request::SendAppToProfileMessage_request(void) : SDLRPCRequest(PROTOCOL_VERSION,Marshaller::METHOD_SENDAPPTOPROFILEMESSAGE_REQUEST),
      profileData(0),
    name(0)
{
}



bool SendAppToProfileMessage_request::set_profileData(const std::string& profileData_)
{
  delete profileData;
  profileData=0;

  profileData=new std::string(profileData_);
  return true;
}

void SendAppToProfileMessage_request::reset_profileData(void)
{
  if(profileData)
    delete profileData;
  profileData=0;
}

bool SendAppToProfileMessage_request::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void SendAppToProfileMessage_request::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}




const std::string* SendAppToProfileMessage_request::get_profileData(void) const 
{
  return profileData;
}

const std::string* SendAppToProfileMessage_request::get_name(void) const 
{
  return name;
}

