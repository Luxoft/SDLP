//
// Copyright (c) 2013, Ford Motor Company
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following
// disclaimer in the documentation and/or other materials provided with the
// distribution.
//
// Neither the name of the Ford Motor Company nor the names of its contributors
// may be used to endorse or promote products derived from this software
// without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

#ifndef NSSMARTDEVICELINKKRPCV2_ONENCODEDSYNCPDATA_INCLUDE
#define NSSMARTDEVICELINKKRPCV2_ONENCODEDSYNCPDATA_INCLUDE

#include <vector>
#include <string>

#include "JSONHandler/SDLRPCMessage.h"


/*
  interface	Ford Sync RAPI
  version	2.0O
  date		2012-11-02
  generated at	Thu Jan 24 06:36:23 2013
  source stamp	Thu Jan 24 06:35:41 2013
  author	RC
*/

namespace NsSmartDeviceLinkRPCV2
{

///  Callback including encoded data of any SyncP packets that SYNC needs to send back to the mobile device.

  class OnEncodedSyncPData : public NsSmartDeviceLinkRPC::SDLRPCMessage
  {
  public:
  
    OnEncodedSyncPData(const OnEncodedSyncPData& c);
    OnEncodedSyncPData(void);
    
    virtual ~OnEncodedSyncPData(void);
  
    OnEncodedSyncPData& operator =(const OnEncodedSyncPData&);
  
    bool checkIntegrity(void);

    const std::vector<std::string>& get_data(void) const;
    const std::string* get_URL(void) const;
    const int* get_Timeout(void) const;

    bool set_data(const std::vector<std::string>& data_);
    void reset_URL(void);
    bool set_URL(const std::string& URL_);
    void reset_Timeout(void);
    bool set_Timeout(int Timeout_);

  private:
  
    friend class OnEncodedSyncPDataMarshaller;


///  Contains base64 encoded string of SyncP packets.
      std::vector<std::string> data;	//!<   [%s..%s] (10000)

/**
     If blank, the SyncP data shall be forwarded to the app.
     If not blank, the SyncP data shall be forwarded to the provided URL.
*/
      std::string* URL;	//!< (1000)

/**
     If blank, the SyncP data shall be forwarded to the app.
     If not blank, the SyncP data shall be forwarded with the provided timeout in seconds.
*/
      int* Timeout;	//!<  (-2000000000,2000000000)
  };

}

#endif
