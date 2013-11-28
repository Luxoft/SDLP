#ifndef NSSMARTDEVICELINKRPCV2_APPSTATECHANGED_REQUEST_INCLUDE
#define NSSMARTDEVICELINKRPCV2_APPSTATECHANGED_REQUEST_INCLUDE

#include <string>

#include "../V1/MobileAppState.h"
#include "../include/JSONHandler/SDLRPCRequest.h"


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

///  Informs profile about mobile application state change.

  class AppStateChanged_request : public NsSmartDeviceLinkRPC::SDLRPCRequest
  {
  public:
  
    AppStateChanged_request(const AppStateChanged_request& c);
    AppStateChanged_request(void);
    
    virtual ~AppStateChanged_request(void);
  
    AppStateChanged_request& operator =(const AppStateChanged_request&);
  
    bool checkIntegrity(void);

    const std::string* get_name(void) const;
    const NsSmartDeviceLinkRPC::MobileAppState* get_state(void) const;

    void reset_name(void);
    bool set_name(const std::string& name_);
    void reset_state(void);
    bool set_state(const NsSmartDeviceLinkRPC::MobileAppState& state_);

  private:
  
    friend class AppStateChanged_requestMarshaller;


///  Unique profile name.
      std::string* name;	//!< (1000)

///  Describes mobile app state.
      NsSmartDeviceLinkRPC::MobileAppState* state;
  };

}

#endif
