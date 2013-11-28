#include "../include/JSONHandler/SDLRPCObjects/V1/SendAppToProfileMessage_response.h"
#include "SendAppToProfileMessage_responseMarshaller.h"
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
SendAppToProfileMessage_response& SendAppToProfileMessage_response::operator =(const SendAppToProfileMessage_response& c)
{
  resultCode= c.resultCode;
  info= c.info ? new std::string(c.info[0]) : 0;

  return *this;}


SendAppToProfileMessage_response::~SendAppToProfileMessage_response(void)
{
  if(info)
    delete info;
}


SendAppToProfileMessage_response::SendAppToProfileMessage_response(const SendAppToProfileMessage_response& c)
{
  *this=c;
}


bool SendAppToProfileMessage_response::checkIntegrity(void)
{
  return SendAppToProfileMessage_responseMarshaller::checkIntegrity(*this);
}


SendAppToProfileMessage_response::SendAppToProfileMessage_response(void) : SDLRPCResponse(PROTOCOL_VERSION,Marshaller::METHOD_SENDAPPTOPROFILEMESSAGE_RESPONSE),
      info(0)
{
}



bool SendAppToProfileMessage_response::set_resultCode(const Result& resultCode_)
{
  if(!ResultMarshaller::checkIntegrityConst(resultCode_))   return false;
  resultCode=resultCode_;
  return true;
}

bool SendAppToProfileMessage_response::set_info(const std::string& info_)
{
  if(info_.length()>1000)  return false;
  delete info;
  info=0;

  info=new std::string(info_);
  return true;
}

void SendAppToProfileMessage_response::reset_info(void)
{
  if(info)
    delete info;
  info=0;
}




const Result& SendAppToProfileMessage_response::get_resultCode(void) const 
{
  return resultCode;
}

const std::string* SendAppToProfileMessage_response::get_info(void) const 
{
  return info;
}

