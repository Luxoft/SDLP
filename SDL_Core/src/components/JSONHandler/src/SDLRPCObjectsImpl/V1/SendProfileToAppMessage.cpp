#include "../include/JSONHandler/SDLRPCObjects/V1/SendProfileToAppMessage.h"
#include "SendProfileToAppMessageMarshaller.h"
#include "../include/JSONHandler/SDLRPCObjects/V1/Marshaller.h"

#define PROTOCOL_VERSION	1


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jun 24 12:39:25 2013
  source stamp	Mon Jun 24 12:23:03 2013
  author	RC
*/

using namespace NsSmartDeviceLinkRPC;
SendProfileToAppMessage& SendProfileToAppMessage::operator =(const SendProfileToAppMessage& c)
{
  name= c.name ? new std::string(c.name[0]) : 0;
  data= c.data;

  return *this;}


SendProfileToAppMessage::~SendProfileToAppMessage(void)
{
  if(name)
    delete name;
}


SendProfileToAppMessage::SendProfileToAppMessage(const SendProfileToAppMessage& c)
{
  *this=c;
}


bool SendProfileToAppMessage::checkIntegrity(void)
{
  return SendProfileToAppMessageMarshaller::checkIntegrity(*this);
}


SendProfileToAppMessage::SendProfileToAppMessage(void) : SDLRPCNotification(PROTOCOL_VERSION,Marshaller::METHOD_SENDPROFILETOAPPMESSAGE),
      name(0)
{
}



bool SendProfileToAppMessage::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void SendProfileToAppMessage::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}

bool SendProfileToAppMessage::set_data(const std::string& data_)
{
  data=data_;
  return true;
}




const std::string* SendProfileToAppMessage::get_name(void) const 
{
  return name;
}

const std::string& SendProfileToAppMessage::get_data(void) const 
{
  return data;
}

