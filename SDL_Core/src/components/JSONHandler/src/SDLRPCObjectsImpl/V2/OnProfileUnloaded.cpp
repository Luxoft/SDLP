#include "../include/JSONHandler/SDLRPCObjects/V2/OnProfileUnloaded.h"
#include "OnProfileUnloadedMarshaller.h"
#include "../include/JSONHandler/SDLRPCObjects/V2/Marshaller.h"
#include "ActionPerformerMarshaller.h"

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
OnProfileUnloaded& OnProfileUnloaded::operator =(const OnProfileUnloaded& c)
{
  name= c.name ? new std::string(c.name[0]) : 0;
  performer= c.performer;

  return *this;}


OnProfileUnloaded::~OnProfileUnloaded(void)
{
  if(name)
    delete name;
}


OnProfileUnloaded::OnProfileUnloaded(const OnProfileUnloaded& c)
{
  *this=c;
}


bool OnProfileUnloaded::checkIntegrity(void)
{
  return OnProfileUnloadedMarshaller::checkIntegrity(*this);
}


OnProfileUnloaded::OnProfileUnloaded(void) : 
    NsSmartDeviceLinkRPC::SDLRPCNotification(PROTOCOL_VERSION),
    name(0)
{
}



bool OnProfileUnloaded::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void OnProfileUnloaded::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}

bool OnProfileUnloaded::set_performer(const ActionPerformer& performer_)
{
  if(!ActionPerformerMarshaller::checkIntegrityConst(performer_))   return false;
  performer=performer_;
  return true;
}




const std::string* OnProfileUnloaded::get_name(void) const 
{
  return name;
}

const ActionPerformer& OnProfileUnloaded::get_performer(void) const 
{
  return performer;
}

