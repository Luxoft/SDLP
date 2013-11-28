#ifndef NSSMARTDEVICELINKRPCV2_PROFILESTATE_INCLUDE
#define NSSMARTDEVICELINKRPCV2_PROFILESTATE_INCLUDE


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

///  Enumeraction that describes current state of profile.

  class ProfileState
  {
  public:
    enum ProfileStateInternal
    {
      INVALID_ENUM=-1,
      FOREGROUND=0,
      LIMITED=1,
      BACKGROUND=2
    };

    ProfileState() : mInternal(INVALID_ENUM)				{}
    ProfileState(ProfileStateInternal e) : mInternal(e)		{}

    ProfileStateInternal get(void) const	{ return mInternal; }
    void set(ProfileStateInternal e)		{ mInternal=e; }

  private:
    ProfileStateInternal mInternal;
    friend class ProfileStateMarshaller;
  };
  
}

#endif
