#include "../include/JSONHandler/SDLRPCObjects/V2/OnProfileStateChanged.h"
#include "OnProfileStateChangedMarshaller.h"
#include "../include/JSONHandler/SDLRPCObjects/V2/Marshaller.h"
#include "ProfileStateMarshaller.h"

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
OnProfileStateChanged& OnProfileStateChanged::operator =(const OnProfileStateChanged& c)
{
  name= c.name ? new std::string(c.name[0]) : 0;
  state= c.state;

  return *this;}


OnProfileStateChanged::~OnProfileStateChanged(void)
{
  if(name)
    delete name;
}


OnProfileStateChanged::OnProfileStateChanged(const OnProfileStateChanged& c)
{
  *this=c;
}


bool OnProfileStateChanged::checkIntegrity(void)
{
  return OnProfileStateChangedMarshaller::checkIntegrity(*this);
}


OnProfileStateChanged::OnProfileStateChanged(void) : 
    NsSmartDeviceLinkRPC::SDLRPCNotification(PROTOCOL_VERSION),
    name(0)
{
}



bool OnProfileStateChanged::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void OnProfileStateChanged::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}

bool OnProfileStateChanged::set_state(const ProfileState& state_)
{
  if(!ProfileStateMarshaller::checkIntegrityConst(state_))   return false;
  state=state_;
  return true;
}




const std::string* OnProfileStateChanged::get_name(void) const 
{
  return name;
}

const ProfileState& OnProfileStateChanged::get_state(void) const 
{
  return state;
}

