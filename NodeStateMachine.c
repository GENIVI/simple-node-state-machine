#include <gio/gio.h>                 /* Access dbus using glib          */

#include "NodeStateMachine.h"    /* Own header file                 */
#include "NodeStateTypes.h"          /* Know the types of the NSM       */
#include "NodeStateManager.h"	     /* Access inhternal NSM interfaces */

#include "SimpleNodeStateMachineApi.h" /* Dbus interface offered by NSMC  */

#include <stdio.h>


static gboolean NSM__handle_shutdown(NodeStateOrgGeniviSimpleNodeStateMachine   *pTestMachine,
        GDBusMethodInvocation *pInvocation,
        gpointer               pUserData)
{

    NsmErrorStatus_e retVal;
    const NsmDataType_e enDataType = NsmDataType_NodeState;
    const NsmNodeState_e nsmNodeState = NsmNodeState_ShuttingDown;

    retVal = NsmSetData(enDataType,
            (unsigned char *)&nsmNodeState,
            sizeof(NsmDataType_NodeState));

    if (retVal != NsmErrorStatus_Ok) {
        log_error() << "Failed to set nsm data " << retVal;
    }

    return TRUE;
}


static NodeStateOrgGeniviSimpleNodeStateMachine *TSTMSC__pTestMachine = NULL;
static GDBusConnection *TSTMSC__pConnection  = NULL;

static void on_name_acquired (GDBusConnection *connection,
        const gchar *name,
        gpointer user_data)
{
    if(g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(TSTMSC__pTestMachine),
                TSTMSC__pConnection,
                "/org/genivi/SimpleNodeStateMachine",
                NULL) == TRUE)
    {
        (void) g_signal_connect(TSTMSC__pTestMachine, "handle_shutdown",
                G_CALLBACK(NSM__handle_shutdown),
                NULL);
    }
    else
    {
        printf("Failed to export skeleton\n");
    }
}

unsigned char NsmcInit(void)
{
    GError *gerr = NULL;

    printf("NsmcInit\n");

    TSTMSC__pTestMachine = node_state_org_genivi_simple_node_state_machine_skeleton_new();
    if (TSTMSC__pTestMachine == NULL)
    {
        g_warning("pTestMachine is Null");
    }
    TSTMSC__pConnection  = g_bus_get_sync(G_BUS_TYPE_SESSION, NULL, &gerr);
    if (TSTMSC__pConnection == NULL)
    {
        printf("pconnection error: %s\n", gerr->message);
    }
    g_bus_own_name (G_BUS_TYPE_SESSION,
            "org.genivi.SimpleNodeStateMachine",
            G_BUS_NAME_OWNER_FLAGS_NONE,
            NULL,
            on_name_acquired,
            NULL,
            NULL,
            NULL);


    return 1;
}


unsigned char NsmcLucRequired(void)
{
    return 1;
}


unsigned char NsmcRequestNodeRestart(NsmRestartReason_e enRestartReason, unsigned int u32RestartType)
{
    printf("NSMC: NsmcRequestNodeRestart called. Restart reason: %d. RestartType: 0x%02X\n", enRestartReason, u32RestartType);
    return 1;
}


unsigned int NsmcGetInterfaceVersion(void)
{
    return (unsigned int) NSMC_INTERFACE_VERSION;
}


NsmErrorStatus_e NsmcSetData(NsmDataType_e enData, unsigned char *pData, unsigned int u32DataLen)
{
    if((enData == NsmDataType_NodeState)
            && (u32DataLen == sizeof(NsmNodeState_e)
            && ((NsmNodeState_e) *pData) == NsmNodeState_Shutdown))
    {
        g_object_unref(TSTMSC__pConnection);
        g_object_unref(TSTMSC__pTestMachine);
    }

    return NsmErrorStatus_Ok;
}
