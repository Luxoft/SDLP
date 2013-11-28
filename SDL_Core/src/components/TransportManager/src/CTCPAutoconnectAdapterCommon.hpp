#ifndef __CTCP_AUTOCONNECT_ADAPTER_COMMON_HPP__
#define __CTCP_AUTOCONNECT_ADAPTER_COMMON_HPP__

#define BRD_MESSAGE_TEXT "SMARTDEVICELINK"
#define NAME_LENGTH 32
#define UUID_LENGTH 36

struct tBrdMessage
{
    char handshake[sizeof(BRD_MESSAGE_TEXT)];
    int32_t boundTcpPortNumber;                        
    char name[NAME_LENGTH];
    char uuid[UUID_LENGTH];
} __attribute__((__packed__));


#endif //
