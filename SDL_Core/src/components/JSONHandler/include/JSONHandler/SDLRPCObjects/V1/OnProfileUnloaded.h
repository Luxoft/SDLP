#ifndef NSSMARTDEVICELINKRPC_ONPROFILEUNLOADED_INCLUDE
#define NSSMARTDEVICELINKRPC_ONPROFILEUNLOADED_INCLUDE

#include <string>

#include "ActionPerformer.h"
#include "../include/JSONHandler/SDLRPCNotification.h"


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

///  Notifies mobile application that profile was unloaded by SDL.

  class OnProfileUnloaded : public SDLRPCNotification
  {
  public:
  
    OnProfileUnloaded(const OnProfileUnloaded& c);
    OnProfileUnloaded(void);
    
    virtual ~OnProfileUnloaded(void);
  
    OnProfileUnloaded& operator =(const OnProfileUnloaded&);
  
    bool checkIntegrity(void);

    const std::string* get_name(void) const;
    const ActionPerformer& get_performer(void) const;

    void reset_name(void);
    bool set_name(const std::string& name_);
    bool set_performer(const ActionPerformer& performer_);

  private:
  
    friend class OnProfileUnloadedMarshaller;


///  Unique profile name.
      std::string* name;	//!< (1000)

///  Describes who did the action.
      ActionPerformer performer;
  };

}

#endif
