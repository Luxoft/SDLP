#include "../include/JSONHandler/SDLRPCObjects/V1/LoadProfile_response.h"
#include "LoadProfile_responseMarshaller.h"
#include "../include/JSONHandler/SDLRPCObjects/V1/Marshaller.h"
#include "ResultMarshaller.h"

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
LoadProfile_response& LoadProfile_response::operator =(const LoadProfile_response& c)
{
  resultCode= c.resultCode;
  info= c.info ? new std::string(c.info[0]) : 0;

  return *this;}


LoadProfile_response::~LoadProfile_response(void)
{
  if(info)
    delete info;
}


LoadProfile_response::LoadProfile_response(const LoadProfile_response& c)
{
  *this=c;
}


bool LoadProfile_response::checkIntegrity(void)
{
  return LoadProfile_responseMarshaller::checkIntegrity(*this);
}


LoadProfile_response::LoadProfile_response(void) : SDLRPCResponse(PROTOCOL_VERSION,Marshaller::METHOD_LOADPROFILE_RESPONSE),
      info(0)
{
}



bool LoadProfile_response::set_resultCode(const Result& resultCode_)
{
  if(!ResultMarshaller::checkIntegrityConst(resultCode_))   return false;
  resultCode=resultCode_;
  return true;
}

bool LoadProfile_response::set_info(const std::string& info_)
{
  if(info_.length()>1000)  return false;
  delete info;
  info=0;

  info=new std::string(info_);
  return true;
}

void LoadProfile_response::reset_info(void)
{
  if(info)
    delete info;
  info=0;
}




const Result& LoadProfile_response::get_resultCode(void) const 
{
  return resultCode;
}

const std::string* LoadProfile_response::get_info(void) const 
{
  return info;
}

