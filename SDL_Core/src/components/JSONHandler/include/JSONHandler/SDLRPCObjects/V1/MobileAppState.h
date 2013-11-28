#ifndef NSSMARTDEVICELINKRPC_MOBILEAPPSTATE_INCLUDE
#define NSSMARTDEVICELINKRPC_MOBILEAPPSTATE_INCLUDE


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

///  Enumeration that describes possible states of connected mobile application.

  class MobileAppState
  {
  public:
    enum MobileAppStateInternal
    {
      INVALID_ENUM=-1,
      MOBILE_APP_FOREGROUND=0,
      MOBILE_APP_BACKGROUND=1,
      MOBILE_APP_LOCK_SCREEN=2
    };
  
    MobileAppState() : mInternal(INVALID_ENUM)				{}
    MobileAppState(MobileAppStateInternal e) : mInternal(e)		{}
  
    MobileAppStateInternal get(void) const	{ return mInternal; }
    void set(MobileAppStateInternal e)		{ mInternal=e; }
  
  private:
    MobileAppStateInternal mInternal;
    friend class MobileAppStateMarshaller;
  };
  
}

#endif
