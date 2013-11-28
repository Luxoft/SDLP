#include "../include/JSONHandler/SDLRPCObjects/V1/OnProfileToAppMessage.h"
#include "OnProfileToAppMessageMarshaller.h"
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
OnProfileToAppMessage& OnProfileToAppMessage::operator =(const OnProfileToAppMessage& c)
{
  name= c.name ? new std::string(c.name[0]) : 0;
  data= c.data;

  return *this;}


OnProfileToAppMessage::~OnProfileToAppMessage(void)
{
  if(name)
    delete name;
}


OnProfileToAppMessage::OnProfileToAppMessage(const OnProfileToAppMessage& c)
{
  *this=c;
}


bool OnProfileToAppMessage::checkIntegrity(void)
{
  return OnProfileToAppMessageMarshaller::checkIntegrity(*this);
}


OnProfileToAppMessage::OnProfileToAppMessage(void) : SDLRPCNotification(PROTOCOL_VERSION,Marshaller::METHOD_ONPROFILETOAPPMESSAGE),
      name(0)
{
}



bool OnProfileToAppMessage::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void OnProfileToAppMessage::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}

bool OnProfileToAppMessage::set_data(const std::string& data_)
{
  data=data_;
  return true;
}




const std::string* OnProfileToAppMessage::get_name(void) const 
{
  return name;
}

const std::string& OnProfileToAppMessage::get_data(void) const 
{
  return data;
}

