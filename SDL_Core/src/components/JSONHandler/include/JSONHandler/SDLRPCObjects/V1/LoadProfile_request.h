#ifndef NSSMARTDEVICELINKRPC_LOADPROFILE_REQUEST_INCLUDE
#define NSSMARTDEVICELINKRPC_LOADPROFILE_REQUEST_INCLUDE

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

///  Requests head unit to load profile.

  class LoadProfile_request : public SDLRPCRequest
  {
  public:
  
    LoadProfile_request(const LoadProfile_request& c);
    LoadProfile_request(void);
    
    virtual ~LoadProfile_request(void);
  
    LoadProfile_request& operator =(const LoadProfile_request&);
  
    bool checkIntegrity(void);

    const std::string* get_name(void) const;

    void reset_name(void);
    bool set_name(const std::string& name_);

  private:
  
    friend class LoadProfile_requestMarshaller;


///  Unique profile name.
      std::string* name;	//!< (1000)
  };

}

#endif
