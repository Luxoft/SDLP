#ifndef NSSMARTDEVICELINKRPC_APPTOPROFILEMESSAGE_RESPONSE_INCLUDE
#define NSSMARTDEVICELINKRPC_APPTOPROFILEMESSAGE_RESPONSE_INCLUDE

#include <string>

#include "Result.h"
#include "../include/JSONHandler/SDLRPCResponse.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Sun Jun 23 21:44:22 2013
  source stamp	Sun Jun 23 21:44:15 2013
  author	RC
*/

namespace NsSmartDeviceLinkRPC
{

  class AppToProfileMessage_response : public SDLRPCResponse
  {
  public:
  
    AppToProfileMessage_response(const AppToProfileMessage_response& c);
    AppToProfileMessage_response(void);
    
    virtual ~AppToProfileMessage_response(void);
  
    AppToProfileMessage_response& operator =(const AppToProfileMessage_response&);
  
    bool checkIntegrity(void);

    const Result& get_resultCode(void) const;
    const std::string* get_info(void) const;

    bool set_resultCode(const Result& resultCode_);
    void reset_info(void);
    bool set_info(const std::string& info_);

  private:
  
    friend class AppToProfileMessage_responseMarshaller;


///  See Result
      Result resultCode;

///  Provides additional human readable info regarding the result.
      std::string* info;	//!< (1000)
  };

}

#endif
