#include "../include/JSONHandler/SDLRPCObjects/V1/RemoveProfile_response.h"
#include "RemoveProfile_responseMarshaller.h"
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
RemoveProfile_response& RemoveProfile_response::operator =(const RemoveProfile_response& c)
{
  resultCode= c.resultCode;
  info= c.info ? new std::string(c.info[0]) : 0;

  return *this;}


RemoveProfile_response::~RemoveProfile_response(void)
{
  if(info)
    delete info;
}


RemoveProfile_response::RemoveProfile_response(const RemoveProfile_response& c)
{
  *this=c;
}


bool RemoveProfile_response::checkIntegrity(void)
{
  return RemoveProfile_responseMarshaller::checkIntegrity(*this);
}


RemoveProfile_response::RemoveProfile_response(void) : SDLRPCResponse(PROTOCOL_VERSION,Marshaller::METHOD_REMOVEPROFILE_RESPONSE),
      info(0)
{
}



bool RemoveProfile_response::set_resultCode(const Result& resultCode_)
{
  if(!ResultMarshaller::checkIntegrityConst(resultCode_))   return false;
  resultCode=resultCode_;
  return true;
}

bool RemoveProfile_response::set_info(const std::string& info_)
{
  if(info_.length()>1000)  return false;
  delete info;
  info=0;

  info=new std::string(info_);
  return true;
}

void RemoveProfile_response::reset_info(void)
{
  if(info)
    delete info;
  info=0;
}




const Result& RemoveProfile_response::get_resultCode(void) const 
{
  return resultCode;
}

const std::string* RemoveProfile_response::get_info(void) const 
{
  return info;
}

