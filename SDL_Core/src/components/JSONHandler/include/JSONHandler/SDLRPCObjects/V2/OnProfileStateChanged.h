#ifndef NSSMARTDEVICELINKRPCV2_ONPROFILESTATECHANGED_INCLUDE
#define NSSMARTDEVICELINKRPCV2_ONPROFILESTATECHANGED_INCLUDE

#include <string>

#include "ProfileState.h"
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

///  Notifies mobile application that profile state was changed

  class OnProfileStateChanged : public NsSmartDeviceLinkRPC::SDLRPCNotification
  {
  public:
  
    OnProfileStateChanged(const OnProfileStateChanged& c);
    OnProfileStateChanged(void);
    
    virtual ~OnProfileStateChanged(void);
  
    OnProfileStateChanged& operator =(const OnProfileStateChanged&);
  
    bool checkIntegrity(void);

    const std::string* get_name(void) const;
    const ProfileState& get_state(void) const;

    void reset_name(void);
    bool set_name(const std::string& name_);
    bool set_state(const ProfileState& state_);

  private:
  
    friend class OnProfileStateChangedMarshaller;


///  Unique profile name.
      std::string* name;	//!< (1000)

///  Describes state of a profile.
      ProfileState state;
  };

}

#endif
