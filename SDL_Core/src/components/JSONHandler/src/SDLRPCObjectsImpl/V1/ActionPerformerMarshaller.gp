%language=C++
%struct-type
%define lookup-function-name getPointer
%define class-name ActionPerformer_intHash
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
AP_SYSTEM,0
AP_USER,1
