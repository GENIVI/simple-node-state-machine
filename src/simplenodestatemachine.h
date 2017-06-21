#ifndef SIMPLE_NODE_STATE_MACHINE_H
#define SIMPLE_NODE_STATE_MACHINE_H

#define NSMC_INTERFACE_VERSION    0x01000000U

#include <NodeStateTypes.h>

#ifdef __cplusplus
extern "C" {
#endif

unsigned char NsmcInit();
unsigned char NsmcLucRequired();
unsigned char NsmcRequestNodeRestart(NsmRestartReason_e enRestartReason,
                                     unsigned int u32RestartType);

unsigned int NsmcGetInterfaceVersion();

NsmErrorStatus_e NsmcSetData(NsmDataType_e enData,
                             unsigned char *pData,
                             unsigned int u32DataLen);

NsmErrorStatus_e NsmcHandleShutdownRequest();

#ifdef __cplusplus
}
#endif


#endif

