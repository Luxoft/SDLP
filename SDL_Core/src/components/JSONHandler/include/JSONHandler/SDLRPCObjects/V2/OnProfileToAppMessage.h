#ifndef NSSMARTDEVICELINKRPCV2_ONPROFILETOAPPMESSAGE_INCLUDE
#define NSSMARTDEVICELINKRPCV2_ONPROFILETOAPPMESSAGE_INCLUDE

#include <string>

#include "../include/JSONHandler/SDLRPCNotification.h"


/*
  interface	Ford Sync RAPI
  version	1.2
  date		2011-05-17
  generated at	Mon Jul  1 13:13:32 2013
  source stamp	Sun Jun 30 21:55:31 2013
  author	RC
*/

namespace NsSmartDeviceLinkRPCV2
{

///  Sends message from profile to mobile application.

  class OnProfileToAppMessage : public NsSmartDeviceLinkRPC::SDLRPCNotification
  {
  public:
  
    OnProfileToAppMessage(const OnProfileToAppMessage& c);
    OnProfileToAppMessage(void);
    
    virtual ~OnProfileToAppMessage(void);
  
    OnProfileToAppMessage& operator =(const OnProfileToAppMessage&);
  
    bool checkIntegrity(void);

    const std::string* get_name(void) const;
    const std::string& get_data(void) const;

    void reset_name(void);
    bool set_name(const std::string& name_);
    bool set_data(const std::string& data_);

  private:
  
    friend class OnProfileToAppMessageMarshaller;


///  Unique profile name.
      std::string* name;	//!< (1000)

///  Binary profile data.
      std::string data;
  };

}

#endif
