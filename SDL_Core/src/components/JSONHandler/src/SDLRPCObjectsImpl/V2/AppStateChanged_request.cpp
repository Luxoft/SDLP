#include "../include/JSONHandler/SDLRPCObjects/V2/AppStateChanged_request.h"
#include "AppStateChanged_requestMarshaller.h"
#include "../include/JSONHandler/SDLRPCObjects/V2/Marshaller.h"
#include "../V1/MobileAppStateMarshaller.h"

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
AppStateChanged_request& AppStateChanged_request::operator =(const AppStateChanged_request& c)
{
  name= c.name ? new std::string(c.name[0]) : 0;
  state= c.state ? new NsSmartDeviceLinkRPC::MobileAppState(c.state[0]) : 0;

  return *this;}


AppStateChanged_request::~AppStateChanged_request(void)
{
  if(name)
    delete name;
  if(state)
    delete state;
}


AppStateChanged_request::AppStateChanged_request(const AppStateChanged_request& c)
{
  *this=c;
}


bool AppStateChanged_request::checkIntegrity(void)
{
  return AppStateChanged_requestMarshaller::checkIntegrity(*this);
}


AppStateChanged_request::AppStateChanged_request(void) : 
    NsSmartDeviceLinkRPC::SDLRPCRequest(PROTOCOL_VERSION),
    name(0),
    state(0)
{
}



bool AppStateChanged_request::set_name(const std::string& name_)
{
  if(name_.length()>1000)  return false;
  delete name;
  name=0;

  name=new std::string(name_);
  return true;
}

void AppStateChanged_request::reset_name(void)
{
  if(name)
    delete name;
  name=0;
}

bool AppStateChanged_request::set_state(const NsSmartDeviceLinkRPC::MobileAppState& state_)
{
  if(!NsSmartDeviceLinkRPC::MobileAppStateMarshaller::checkIntegrityConst(state_))   return false;
  delete state;
  state=0;

  state=new NsSmartDeviceLinkRPC::MobileAppState(state_);
  return true;
}

void AppStateChanged_request::reset_state(void)
{
  if(state)
    delete state;
  state=0;
}




const std::string* AppStateChanged_request::get_name(void) const 
{
  return name;
}

const NsSmartDeviceLinkRPC::MobileAppState* AppStateChanged_request::get_state(void) const 
{
  return state;
}

