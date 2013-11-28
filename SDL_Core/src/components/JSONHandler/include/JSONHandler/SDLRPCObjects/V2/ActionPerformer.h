#ifndef NSSMARTDEVICELINKRPCV2_ACTIONPERFORMER_INCLUDE
#define NSSMARTDEVICELINKRPCV2_ACTIONPERFORMER_INCLUDE


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

///  Enumeration that describes who did the action.

  class ActionPerformer
  {
  public:
    enum ActionPerformerInternal
    {
      INVALID_ENUM=-1,
      AP_SYSTEM=0,
      AP_USER=1
    };
  
    ActionPerformer() : mInternal(INVALID_ENUM)				{}
    ActionPerformer(ActionPerformerInternal e) : mInternal(e)		{}
  
    ActionPerformerInternal get(void) const	{ return mInternal; }
    void set(ActionPerformerInternal e)		{ mInternal=e; }
  
  private:
    ActionPerformerInternal mInternal;
    friend class ActionPerformerMarshaller;
  };
  
}

#endif
