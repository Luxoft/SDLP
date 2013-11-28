/**
 *
 * SDLP SDK
 * Cross Platform Application Communication Stack for In-Vehicle Applications
 *
 * Copyright (C) 2013, Luxoft Professional Corp., member of IBS group
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; version 2.1.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 *
 *
 */
/**
 * @author Elena Bratanova <ebratanova@luxoft.com>
 */

#include <string.h>

#include "ProfileManagerUtils/RpcParser.h"

using namespace NsProfileManager;

const unsigned char RPC_REQUEST = 0x0;
const unsigned char RPC_RESPONSE = 0x1;
const unsigned char RPC_NOTIFICATION = 0x2;
const unsigned char RPC_UNKNOWN = 0xF;

bool RpcParser::isIviLinkMessage(NsSmartDeviceLinkRPC::SDLRPCMessage * message)
{
    if (message == NULL)
    {
        return false;
    }
    return (message->getMethodId() == NsSmartDeviceLinkRPC::Marshaller::METHOD_PROFILEREQUESTTOHMI 
         || message->getMethodId() == NsSmartDeviceLinkRPC::Marshaller::METHOD_ONHMIREQUESTTOPROFILE);
}

NsSmartDeviceLinkRPC::SDLRPCNotification* RpcParser::parseNotificationV1(const char * data, const int dataSize)
{
    if (data == 0 || dataSize == 0)
    {
        return NULL;
    }
    std::string json(data, dataSize);
    if (json.empty())
    {
        return NULL;
    }
    return (NsSmartDeviceLinkRPC::SDLRPCNotification*)NsSmartDeviceLinkRPC::Marshaller::fromString(json);
}

NsSmartDeviceLinkRPC::SDLRPCMessage* RpcParser::parseNotificationV2(const char * data, const int dataSize)
{
    return parseMessageV2(data, dataSize);
}

NsSmartDeviceLinkRPC::SDLRPCResponse* RpcParser::parseResponseV1(const char * data, const int dataSize)
{
    if (data == 0 || dataSize == 0)
    {
        return NULL;
    }
    
    std::string json(data, dataSize);
    if (json.empty())
    {
        return NULL;
    }

    return (NsSmartDeviceLinkRPC::SDLRPCResponse*)NsSmartDeviceLinkRPC::Marshaller::fromString(json);
}

NsSmartDeviceLinkRPC::SDLRPCResponse* RpcParser::parseResponseV2(const char * data, const int dataSize)
{
    NsSmartDeviceLinkRPC::SDLRPCMessage * msg = parseMessageV2(data, dataSize);
    if (msg != NULL && msg->getMessageType() == RPC_RESPONSE)
    {
        return (NsSmartDeviceLinkRPC::SDLRPCResponse*) msg;
    }
    return 0;
}

NsSmartDeviceLinkRPC::SDLRPCRequest* RpcParser::parseRequestV1(const char * data, const int dataSize)
{
    if (data == 0 || dataSize == 0)
    {
        return NULL;
    }
    
    std::string json(data, dataSize);
    if (json.empty())
    {
        return NULL;
    }
    return (NsSmartDeviceLinkRPC::SDLRPCRequest*)NsSmartDeviceLinkRPC::Marshaller::fromString(json);
}

NsSmartDeviceLinkRPC::SDLRPCMessage* RpcParser::parseRequestV2(const char * data, const int dataSize)
{
    return parseMessageV2(data, dataSize);
}

SerializedData RpcParser::serializeOutgoingMessage(NsSmartDeviceLinkRPC::SDLRPCMessage * message)
{
    SerializedData result;
    if (message == NULL)
    {
        return result;
    }
    if (message->getProtocolVersion() == 1)
    {
        std::string serialized = NsSmartDeviceLinkRPC::Marshaller::toString(message);
        result.data = new char[serialized.size()];
        memcpy(result.data, serialized.c_str(), serialized.size());
        result.dataSize = serialized.size();
        return result;
    }
    else if (message->getProtocolVersion() == 2)
    {
        additionalIntializationV2Requests(message);
        return serializeMessageV2(message);
    }
    return result;
}

NsSmartDeviceLinkRPC::SDLRPCMessage * RpcParser::parseMessageV2(const char * data, const int dataSize)
{
    unsigned char* receivedData = (unsigned char*)data;
    unsigned char offset = 0;
    unsigned char firstByte = receivedData[offset++];

    int rpcType = -1;
    unsigned char rpcTypeFlag = firstByte >> 4u;
    switch (rpcTypeFlag)
    {
    case RPC_REQUEST:
        rpcType = 0;
        break;
    case RPC_RESPONSE:
        rpcType = 1;
        break;
    case RPC_NOTIFICATION:
        rpcType = 2;
        break;
    default:
        return NULL;
    }

    unsigned int functionId = firstByte >> 8u;

    functionId <<= 24u;
    functionId |= receivedData[offset++] << 16u;
    functionId |= receivedData[offset++] << 8u;
    functionId |= receivedData[offset++];

    unsigned int correlationId = receivedData[offset++] << 24u;
    correlationId |= receivedData[offset++] << 16u;
    correlationId |= receivedData[offset++] << 8u;
    correlationId |= receivedData[offset++];

    unsigned int jsonSize = receivedData[offset++] << 24u;
    jsonSize |= receivedData[offset++] << 16u;
    jsonSize |= receivedData[offset++] << 8u;
    jsonSize |= receivedData[offset++];

    if (jsonSize > dataSize)
    {
        return NULL;
    }

    std::string jsonMessage = std::string((const char*)receivedData + offset, jsonSize);
    if (jsonMessage.length() == 0)
    {
        return NULL;
    }

    std::string jsonCleanMessage = jsonMessage;

    Json::Reader reader;
    Json::Value json;

    if (!reader.parse(jsonCleanMessage, json, false))
    {
        return NULL;
    }

    Json::Value tempSolution;
    tempSolution["parameters"] = json;

    NsSmartDeviceLinkRPC::SDLRPCMessage* messageObject = NsSmartDeviceLinkRPCV2::Marshaller::fromJSON(
                tempSolution,
                static_cast<NsSmartDeviceLinkRPCV2::FunctionID::FunctionIDInternal>(functionId),
                static_cast<NsSmartDeviceLinkRPCV2::messageType::messageTypeInternal>(rpcType));

    if (dataSize > offset + jsonSize)
    {
        std::vector<unsigned char> binaryData(receivedData + offset + jsonSize,
                                              receivedData + dataSize);
        messageObject -> setBinaryData(binaryData);
    }

    messageObject->setMethodId(functionId);

    if (RPC_REQUEST == rpcTypeFlag || RPC_RESPONSE == rpcTypeFlag)
    {
        messageObject->setCorrelationID(correlationId);
    }
    return messageObject;
}

SerializedData RpcParser::serializeMessageV2(NsSmartDeviceLinkRPC::SDLRPCMessage * message)
{
    const uint MAX_HEADER_SIZE = 12;
    Json::Value json = NsSmartDeviceLinkRPCV2::Marshaller::toJSON(message,
                       static_cast<NsSmartDeviceLinkRPCV2::FunctionID::FunctionIDInternal>(message -> getMethodId()),
                       static_cast<NsSmartDeviceLinkRPCV2::messageType::messageTypeInternal>(message -> getMessageType()));
    SerializedData result;
    if (json.isNull())
    {
        if (NsSmartDeviceLinkRPCV2::FunctionID::FunctionIDInternal::OnAudioPassThruID == message->getMethodId())
        {
            const uint MAX_HEADER_SIZE = 12;
            unsigned int jsonSize = 0;
            unsigned int binarySize = 0;
            if (message->getBinaryData())
            {
                binarySize = message->getBinaryData()->size();
            }
            unsigned char* dataForSending = new unsigned char[MAX_HEADER_SIZE + jsonSize + binarySize];
            unsigned char offset = 0;

            unsigned char rpcTypeFlag = RPC_NOTIFICATION;

            unsigned int functionId = message->getMethodId();
            dataForSending[offset++] = ((rpcTypeFlag << 4) & 0xF0) | (functionId >> 24);
            dataForSending[offset++] = functionId >> 16;
            dataForSending[offset++] = functionId >> 8;
            dataForSending[offset++] = functionId;

            unsigned int correlationId = message->getCorrelationID();
            dataForSending[offset++] = correlationId >> 24;
            dataForSending[offset++] = correlationId >> 16;
            dataForSending[offset++] = correlationId >> 8;
            dataForSending[offset++] = correlationId;

            dataForSending[offset++] = jsonSize >> 24;
            dataForSending[offset++] = jsonSize >> 16;
            dataForSending[offset++] = jsonSize >> 8;
            dataForSending[offset++] = jsonSize;

            if (message->getBinaryData())
            {
                const std::vector<unsigned char>& binaryData = *(message->getBinaryData());
                unsigned char* currentPointer = dataForSending + offset + jsonSize;
                for (unsigned int i = 0; i < binarySize; ++i)
                {
                    currentPointer[i] = binaryData[i];
                }
            }

            result.data = (char*)dataForSending;
            result.dataSize = MAX_HEADER_SIZE + jsonSize + binarySize;
            return result;
        }
        else
        {
            return result;
        }
    }

    Json::FastWriter writer;
    std::string messageString = writer.write(json["parameters"]);
    if (messageString.length() == 0)
    {
        return result;
    }

    unsigned int jsonSize = messageString.length() + 1;
    unsigned int binarySize = 0;
    if (message->getBinaryData())
    {
        binarySize = message->getBinaryData()->size();
    }
    unsigned char* dataForSending = new unsigned char[MAX_HEADER_SIZE + jsonSize + binarySize];
    unsigned char offset = 0;

    unsigned char rpcTypeFlag = 0;
    switch (message->getMessageType())
    {
    case 0:
        rpcTypeFlag = RPC_REQUEST;
        break;
    case 1:
        rpcTypeFlag = RPC_RESPONSE;
        break;
    case 2:
        rpcTypeFlag = RPC_NOTIFICATION;
        break;
    }

    unsigned int functionId = message->getMethodId();
    dataForSending[offset++] = ((rpcTypeFlag << 4) & 0xF0) | (functionId >> 24);
    dataForSending[offset++] = functionId >> 16;
    dataForSending[offset++] = functionId >> 8;
    dataForSending[offset++] = functionId;

    unsigned int correlationId = message->getCorrelationID();
    dataForSending[offset++] = correlationId >> 24;
    dataForSending[offset++] = correlationId >> 16;
    dataForSending[offset++] = correlationId >> 8;
    dataForSending[offset++] = correlationId;

    dataForSending[offset++] = jsonSize >> 24;
    dataForSending[offset++] = jsonSize >> 16;
    dataForSending[offset++] = jsonSize >> 8;
    dataForSending[offset++] = jsonSize;

    memcpy(dataForSending + offset, messageString.c_str(), jsonSize);

    if (message->getBinaryData())
    {
        const std::vector<unsigned char>& binaryData = *(message->getBinaryData());
        unsigned char* currentPointer = dataForSending + offset + jsonSize;
        for (unsigned int i = 0; i < binarySize; ++i)
        {
            currentPointer[i] = binaryData[i];
        }
    }

    result.dataSize =  MAX_HEADER_SIZE + jsonSize + binarySize;
    result.data = (char*)dataForSending;
    return result;
}

bool RpcParser::additionalIntializationV2Requests(NsSmartDeviceLinkRPC::SDLRPCMessage * message)
{
    using namespace NsSmartDeviceLinkRPCV2;
    bool found = true;
    if (dynamic_cast<AddCommand_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::AddCommandID);
    }
    else if (dynamic_cast<AddSubMenu_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::AddSubMenuID);
    }
    else if (dynamic_cast<AlertManeuver_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::AlertManeuverID);
    }
    else if (dynamic_cast<Alert_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::AlertID);
    }
    else if (dynamic_cast<ChangeRegistration_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::ChangeRegistrationID);
    }
    else if (dynamic_cast<CreateInteractionChoiceSet_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::CreateInteractionChoiceSetID);
    }
    else if (dynamic_cast<DeleteCommand_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::DeleteCommandID);
    }
    else if (dynamic_cast<DeleteFile_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::DeleteFileID);
    }
    else if (dynamic_cast<DeleteInteractionChoiceSet_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::DeleteInteractionChoiceSetID);
    }
    else if (dynamic_cast<DeleteSubMenu_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::DeleteSubMenuID);
    }
    else if (dynamic_cast<DialNumber_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::DialNumberID);
    }
    else if (dynamic_cast<EncodedSyncPData_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::EncodedSyncPDataID);
    }
    else if (dynamic_cast<EndAudioPassThru_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::EndAudioPassThruID);
    }
    else if (dynamic_cast<GetDTCs_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::GetDTCsID);
    }
    else if (dynamic_cast<GetVehicleData_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::GetVehicleDataID);
    }
    else if (dynamic_cast<ListFiles_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::ListFilesID);
    }
    else if (dynamic_cast<PerformAudioPassThru_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::PerformAudioPassThruID);
    }
    else if (dynamic_cast<PerformInteraction_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::PerformInteractionID);
    }
    else if (dynamic_cast<PutFile_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::PutFileID);
    }
    else if (dynamic_cast<ReadDID_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::ReadDIDID);
    }
    else if (dynamic_cast<RegisterAppInterface_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::RegisterAppInterfaceID);
    }
    else if (dynamic_cast<ResetGlobalProperties_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::ResetGlobalPropertiesID);
    }
    else if (dynamic_cast<ScrollableMessage_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::ScrollableMessageID);
    }
    else if (dynamic_cast<SetAppIcon_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::SetAppIconID);
    }
    else if (dynamic_cast<SetDisplayLayout_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::SetDisplayLayoutID);
    }
    else if (dynamic_cast<SetGlobalProperties_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::SetGlobalPropertiesID);
    }
    else if (dynamic_cast<SetMediaClockTimer_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::SetMediaClockTimerID);
    }
    else if (dynamic_cast<ShowConstantTBT_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::ShowConstantTBTID);
    }
    else if (dynamic_cast<Show_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::ShowID);
    }
    else if (dynamic_cast<Slider_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::SliderID);
    }
    else if (dynamic_cast<Speak_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::SpeakID);
    }
    else if (dynamic_cast<SubscribeButton_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::SubscribeButtonID);
    }
    else if (dynamic_cast<SubscribeVehicleData_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::SubscribeVehicleDataID);
    }
    else if (dynamic_cast<UnregisterAppInterface_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::UnregisterAppInterfaceID);
    }
    else if (dynamic_cast<UnsubscribeButton_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::UnsubscribeButtonID);
    }
    else if (dynamic_cast<UnsubscribeVehicleData_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::UnsubscribeVehicleDataID);
    }
    else if (dynamic_cast<UpdateTurnList_request*>(message) != NULL)
    {
        message->setMethodId(FunctionID::UpdateTurnListID);
    }
    else
    {
        found = false;
    }

    if (found)
    {
        message->setMessageType(NsSmartDeviceLinkRPC::SDLRPCMessage::REQUEST);
    }

    return found;
}
