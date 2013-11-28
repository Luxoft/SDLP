#ifndef NSSMARTDEVICELINKRPCV2_ADDPROFILE_REQUEST_INCLUDE
#define NSSMARTDEVICELINKRPCV2_ADDPROFILE_REQUEST_INCLUDE

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

namespace NsSmartDeviceLinkRPCV2
{

///  Sends message from app into profile.

  class AddProfile_request : public NsSmartDeviceLinkRPC::SDLRPCRequest
  {
  public:
  
    AddProfile_request(const AddProfile_request& c);
    AddProfile_request(void);
    
    virtual ~AddProfile_request(void);
  
    AddProfile_request& operator =(const AddProfile_request&);
  
    bool checkIntegrity(void);

    const std::string* get_name(void) const;
    const std::string* get_profileBinary(void) const;

    void reset_name(void);
    bool set_name(const std::string& name_);
    void reset_profileBinary(void);
    bool set_profileBinary(const std::string& profileBinary_);

  private:
  
    friend class AddProfile_requestMarshaller;


///  Unique profile name.
      std::string* name;	//!< (1000)

///  Binary profile data.
      std::string* profileBinary;
  };

}

#endif
