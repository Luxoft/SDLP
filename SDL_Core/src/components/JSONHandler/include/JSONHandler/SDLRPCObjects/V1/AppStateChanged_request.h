#ifndef NSSMARTDEVICELINKRPC_APPSTATECHANGED_REQUEST_INCLUDE
#define NSSMARTDEVICELINKRPC_APPSTATECHANGED_REQUEST_INCLUDE

#include <string>

#include "MobileAppState.h"
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

///  Informs profile about mobile application state change.

  class AppStateChanged_request : public SDLRPCRequest
  {
  public:
  
    AppStateChanged_request(const AppStateChanged_request& c);
    AppStateChanged_request(void);
    
    virtual ~AppStateChanged_request(void);
  
    AppStateChanged_request& operator =(const AppStateChanged_request&);
  
    bool checkIntegrity(void);

    const std::string* get_name(void) const;
    const MobileAppState* get_state(void) const;

    void reset_name(void);
    bool set_name(const std::string& name_);
    void reset_state(void);
    bool set_state(const MobileAppState& state_);

  private:
  
    friend class AppStateChanged_requestMarshaller;


///  Unique profile name.
      std::string* name;	//!< (1000)

///  Describes mobile app state.
      MobileAppState* state;
  };

}

#endif
