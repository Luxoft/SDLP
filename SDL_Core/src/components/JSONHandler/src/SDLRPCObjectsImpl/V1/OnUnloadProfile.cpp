#include "../include/JSONHandler/SDLRPCObjects/V1/OnUnloadProfile.h"
#include "OnUnloadProfileMarshaller.h"
#include "../include/JSONHandler/SDLRPCObjects/V1/Marshaller.h"
#include "ActionPerformerMarshaller.h"

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
OnUnloadProfile& OnUnloadProfile::operator =(const OnUnloadProfile& c)
{
  name= c.name ? new std::string(c.name[0]) : 0;
  performer= c.performer;

  return *this;}


OnUnloadProfile::~OnUnloadProfile(void)
{
  if(name)
    delete name;
}


OnUnloadProfile::OnUnloadProfile(const OnUnloadProfile& c)
{
  *this=c;
}


bool OnUnloadProfile::checkIntegrity(void)
{
  return OnUnloadProfileMarshaller::checkIntegrity(*this);
}


OnUnloadProfile::OnUnloadProfile(void) : ALRPCNotification(PROTOCOL_VERSION,Marshaller::METHOD_ONUNLOADPROFILE),
      name(0)
{
}



bool OnUnloadProfile::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void OnUnloadProfile::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}

bool OnUnloadProfile::set_performer(const ActionPerformer& performer_)
{
  if(!ActionPerformerMarshaller::checkIntegrityConst(performer_))   return false;
  performer=performer_;
  return true;
}




const std::string* OnUnloadProfile::get_name(void) const 
{
  return name;
}

const ActionPerformer& OnUnloadProfile::get_performer(void) const 
{
  return performer;
}

