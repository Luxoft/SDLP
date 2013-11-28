#ifndef NSSMARTDEVICELINKRPC_REMOVEPROFILE_REQUEST_INCLUDE
#define NSSMARTDEVICELINKRPC_REMOVEPROFILE_REQUEST_INCLUDE

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

///  Requests SDL to remove profile from head unit.

  class RemoveProfile_request : public SDLRPCRequest
  {
  public:
  
    RemoveProfile_request(const RemoveProfile_request& c);
    RemoveProfile_request(void);
    
    virtual ~RemoveProfile_request(void);
  
    RemoveProfile_request& operator =(const RemoveProfile_request&);
  
    bool checkIntegrity(void);

    const std::string* get_name(void) const;

    void reset_name(void);
    bool set_name(const std::string& name_);

  private:
  
    friend class RemoveProfile_requestMarshaller;


///  Unique profile name.
      std::string* name;	//!< (1000)
  };

}

#endif
