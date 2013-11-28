%language=C++
%struct-type
%define lookup-function-name getPointer
%define class-name MobileAppState_intHash
%omit-struct-type
%readonly-tables
%compare-strncmp
%compare-lengths

struct NsSmartDeviceLinkRPC::PerfectHashTable
{
  const char *name;
  unsigned int idx;
};

%%
MOBILE_APP_FOREGROUND,0
MOBILE_APP_BACKGROUND,1
MOBILE_APP_LOCK_SCREEN,2
