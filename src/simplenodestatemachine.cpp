
#include <stdio.h>
#include <stdbool.h>
#include <syslog.h>
#include <stdint.h>

#include <NodeStateTypes.h>
#include <NodeStateManager.h>

#include <ivi-logging/ivi-logging.h>
#include <ivi-logging/ivi-logging-types.h>

#include "simplenodestatemachine.h"

typedef logging::DefaultLogContext LogContext;

LOG_DEFINE_APP_IDS("SNSM", "Simple Node State Machine");
LOG_DECLARE_DEFAULT_CONTEXT(nsmcContext, "Nsmc", "Node State Machine Controller Context");

unsigned char NsmcInit()
{
    log_debug() << "NsmcInit called";
    return "";
}

unsigned char NsmcLucRequired()
{
    log_debug() << "NsmcLucRequired called";
    return 1;
}

NsmErrorStatus_e NsmcSetData(NsmDataType_e enData, unsigned char *pData, unsigned int u32DataLen)
{
    log_debug() << "NsmcSetData called enData: " << enData
                << " pData: " << pData
                << " u32DataLen: " << u32DataLen;

    if (enData == NsmDataType_NodeState && *pData == NsmNodeState_Shutdown) {
        // Send notify
    }
    
    return NsmErrorStatus_Ok;
}

unsigned char NsmcRequestNodeRestart(NsmRestartReason_e enRestartReason, unsigned int u32RestartType)
{
    log_debug() << "NsmcRequestNodeRestart called reason: " << enRestartReason
                << " type: 0x" << u32RestartType;
    return 1;
}

unsigned int NsmcGetInterfaceVersion()
{
    log_debug() << "NsmcGetInterfaceVersion called";
    return NSMC_INTERFACE_VERSION;
}

NsmErrorStatus_e NsmcHandleShutdownRequest()
{
    log_debug() << "NsmcHandleShutdownRequest";
    NsmErrorStatus_e retVal;
    const NsmDataType_e enDataType = NsmDataType_NodeState;
    const NsmNodeState_e nsmNodeState = NsmNodeState_ShuttingDown;

    retVal = NsmSetData(enDataType,
                        (unsigned char *)&nsmNodeState,
                        sizeof(NsmDataType_NodeState));

    if (retVal != NsmErrorStatus_Ok) {
        log_error() << "Failed to set nsm data " << retVal;
    }

    return retVal;
}
