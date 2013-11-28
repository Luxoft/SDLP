#ifndef NSSMARTDEVICELINKRPC_SENDAPPTOPROFILEMESSAGE_REQUEST_INCLUDE
#define NSSMARTDEVICELINKRPC_SENDAPPTOPROFILEMESSAGE_REQUEST_INCLUDE

#include <string>

#include "../include/JSONHandler/SDLRPCRequest.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

namespace NsSmartDeviceLinkRPC
{

///  Sends message from mobile application into profile on head unit.

  class SendAppToProfileMessage_request : public SDLRPCRequest
  {
  public:
  
    SendAppToProfileMessage_request(const SendAppToProfileMessage_request& c);
    SendAppToProfileMessage_request(void);
    
    virtual ~SendAppToProfileMessage_request(void);
  
    SendAppToProfileMessage_request& operator =(const SendAppToProfileMessage_request&);
  
    bool checkIntegrity(void);

    const std::string* get_profileData(void) const;
    const std::string* get_name(void) const;

    void reset_profileData(void);
    bool set_profileData(const std::string& profileData_);
    void reset_name(void);
    bool set_name(const std::string& name_);

  private:
  
    friend class SendAppToProfileMessage_requestMarshaller;


///  Binary profile data.
      std::string* profileData;

///  Unique profile name.
      std::string* name;	//!< (1000)
  };

}

#endif
