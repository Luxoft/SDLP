#ifndef NSSMARTDEVICELINKRPC_APPTOPROFILEMESSAGE_REQUEST_INCLUDE
#define NSSMARTDEVICELINKRPC_APPTOPROFILEMESSAGE_REQUEST_INCLUDE

#include <string>

#include "../include/JSONHandler/SDLRPCRequest.h"


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

///  Sends message from app into profile.

  class AppToProfileMessage_request : public SDLRPCRequest
  {
  public:
  
    AppToProfileMessage_request(const AppToProfileMessage_request& c);
    AppToProfileMessage_request(void);
    
    virtual ~AppToProfileMessage_request(void);
  
    AppToProfileMessage_request& operator =(const AppToProfileMessage_request&);
  
    bool checkIntegrity(void);

    const std::string* get_profileData(void) const;
    const std::string* get_name(void) const;

    void reset_profileData(void);
    bool set_profileData(const std::string& profileData_);
    void reset_name(void);
    bool set_name(const std::string& name_);

  private:
  
    friend class AppToProfileMessage_requestMarshaller;


///  Binary profile data.
      std::string* profileData;

///  Unique profile name.
      std::string* name;	//!< (1000)
  };

}

#endif
