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

#ifndef NSRPC2COMMUNICATION_UI_PERFORMINTERACTIONRESPONSE_INCLUDE
#define NSRPC2COMMUNICATION_UI_PERFORMINTERACTIONRESPONSE_INCLUDE

#include "JSONHandler/RPC2Response.h"

#include "../include/JSONHandler/SDLRPCObjects/V2/TriggerSource.h"

/*
  interface	NsRPC2Communication::UI
  version	1.2
  generated at	Thu Jan 24 06:41:15 2013
  source stamp	Wed Jan 23 13:56:28 2013
  author	RC
*/

namespace NsRPC2Communication
{
  namespace UI
  {

    class PerformInteractionResponse : public ::NsRPC2Communication::RPC2Response
    {
    public:
    
      PerformInteractionResponse(const PerformInteractionResponse& c);
      PerformInteractionResponse(void);
    
      PerformInteractionResponse& operator =(const PerformInteractionResponse&);
    
      virtual ~PerformInteractionResponse(void);
    
      bool checkIntegrity(void);
    
// getters
      const unsigned int* get_choiceID(void);
      const NsSmartDeviceLinkRPCV2::TriggerSource* get_triggerSource(void);

// setters
/// choiceID <= 2000000000
      bool set_choiceID(const unsigned int& choiceID);

      void reset_choiceID(void);

      bool set_triggerSource(const NsSmartDeviceLinkRPCV2::TriggerSource& triggerSource);

      void reset_triggerSource(void);


    private:

      friend class PerformInteractionResponseMarshaller;

      unsigned int* choiceID;
      NsSmartDeviceLinkRPCV2::TriggerSource* triggerSource;

    };
  }
}

#endif
