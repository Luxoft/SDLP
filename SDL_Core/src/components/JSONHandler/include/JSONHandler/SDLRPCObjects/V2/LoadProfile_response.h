#ifndef NSSMARTDEVICELINKRPCV2_LOADPROFILE_RESPONSE_INCLUDE
#define NSSMARTDEVICELINKRPCV2_LOADPROFILE_RESPONSE_INCLUDE

#include <string>

#include "Result.h"
#include "../include/JSONHandler/SDLRPCResponse.h"


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

  class LoadProfile_response : public NsSmartDeviceLinkRPC::SDLRPCResponse
  {
  public:
  
    LoadProfile_response(const LoadProfile_response& c);
    LoadProfile_response(void);
    
    virtual ~LoadProfile_response(void);
  
    LoadProfile_response& operator =(const LoadProfile_response&);
  
    bool checkIntegrity(void);

    const Result& get_resultCode(void) const;
    const std::string* get_info(void) const;

    bool set_resultCode(const Result& resultCode_);
    void reset_info(void);
    bool set_info(const std::string& info_);

  private:
  
    friend class LoadProfile_responseMarshaller;


///  See Result
      Result resultCode;

///  Provides additional human readable info regarding the result.
      std::string* info;	//!< (1000)
  };

}

#endif
