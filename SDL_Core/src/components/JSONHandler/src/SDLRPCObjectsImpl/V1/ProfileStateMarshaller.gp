%language=C++
%struct-type
%define lookup-function-name getPointer
%define class-name ProfileState_intHash
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
FOREGROUND,0
LIMITED,1
BACKGROUND,2
