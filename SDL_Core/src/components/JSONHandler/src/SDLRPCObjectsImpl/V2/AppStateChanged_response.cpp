#include "../include/JSONHandler/SDLRPCObjects/V2/AppStateChanged_response.h"
#include "AppStateChanged_responseMarshaller.h"
#include "../include/JSONHandler/SDLRPCObjects/V2/Marshaller.h"
#include "ResultMarshaller.h"

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
AppStateChanged_response& AppStateChanged_response::operator =(const AppStateChanged_response& c)
{
  resultCode= c.resultCode;
  info= c.info ? new std::string(c.info[0]) : 0;

  return *this;}


AppStateChanged_response::~AppStateChanged_response(void)
{
  if(info)
    delete info;
}


AppStateChanged_response::AppStateChanged_response(const AppStateChanged_response& c)
{
  *this=c;
}


bool AppStateChanged_response::checkIntegrity(void)
{
  return AppStateChanged_responseMarshaller::checkIntegrity(*this);
}


AppStateChanged_response::AppStateChanged_response(void) : 
    NsSmartDeviceLinkRPC::SDLRPCResponse(PROTOCOL_VERSION),
    info(0)
{
}



bool AppStateChanged_response::set_resultCode(const Result& resultCode_)
{
  if(!ResultMarshaller::checkIntegrityConst(resultCode_))   return false;
  resultCode=resultCode_;
  return true;
}

bool AppStateChanged_response::set_info(const std::string& info_)
{
  if(info_.length()>1000)  return false;
  delete info;
  info=0;

  info=new std::string(info_);
  return true;
}

void AppStateChanged_response::reset_info(void)
{
  if(info)
    delete info;
  info=0;
}




const Result& AppStateChanged_response::get_resultCode(void) const 
{
  return resultCode;
}

const std::string* AppStateChanged_response::get_info(void) const 
{
  return info;
}

