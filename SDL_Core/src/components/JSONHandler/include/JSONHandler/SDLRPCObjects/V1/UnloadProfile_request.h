#ifndef NSSMARTDEVICELINKRPC_UNLOADPROFILE_REQUEST_INCLUDE
#define NSSMARTDEVICELINKRPC_UNLOADPROFILE_REQUEST_INCLUDE

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

///  Requests head unit to unload running profile.

  class UnloadProfile_request : public SDLRPCRequest
  {
  public:
  
    UnloadProfile_request(const UnloadProfile_request& c);
    UnloadProfile_request(void);
    
    virtual ~UnloadProfile_request(void);
  
    UnloadProfile_request& operator =(const UnloadProfile_request&);
  
    bool checkIntegrity(void);

    const std::string* get_name(void) const;

    void reset_name(void);
    bool set_name(const std::string& name_);

  private:
  
    friend class UnloadProfile_requestMarshaller;


///  Unique profile name.
      std::string* name;	//!< (1000)
  };

}

#endif
