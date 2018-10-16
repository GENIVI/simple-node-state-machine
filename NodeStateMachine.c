#include <gio/gio.h>                 /* Access dbus using glib          */

#include "NodeStateMachine.h"    /* Own header file                 */
#include "NodeStateTypes.h"          /* Know the types of the NSM       */
#include "NodeStateManager.h"	     /* Access inhternal NSM interfaces */

#include "SimpleNodeStateMachineApi.h" /* Dbus interface offered by NSMC  */

#include <stdio.h>


static gboolean NSM__handle_shutdown(NodeStateOrgGeniviSimpleNodeStateMachine   *pStateMachine,
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
        g_error("Failed to set nsm data %i", retVal);
    }

    return TRUE;
}


static NodeStateOrgGeniviSimpleNodeStateMachine *pStateMachine = NULL;
static GDBusConnection *pConnection  = NULL;

static void on_name_acquired (GDBusConnection *connection,
        const gchar *name,
        gpointer user_data)
{
    if(g_dbus_interface_skeleton_export(G_DBUS_INTERFACE_SKELETON(pStateMachine),
                pConnection,
                "/org/genivi/SimpleNodeStateMachine",
                NULL) == TRUE)
    {
        (void) g_signal_connect(pStateMachine, "handle_shutdown",
                G_CALLBACK(NSM__handle_shutdown),
                NULL);
    }
    else
    {
        g_warning("Failed to export skeleton\n");
    }
}

unsigned char NsmcInit(void)
{
    GError *gerr = NULL;
    unsigned char retval = 1;

    g_info("NsmcInit\n");

    pStateMachine = node_state_org_genivi_simple_node_state_machine_skeleton_new();
    if (pStateMachine == NULL)
    {
        g_warning("pStateMachine is Null");
        retval = 0;
    }
    pConnection  = g_bus_get_sync(G_BUS_TYPE_SYSTEM, NULL, &gerr);
    if (pConnection == NULL)
    {
        g_warning("pconnection error: %s\n", gerr->message);
        retval = 0;
    }
    g_bus_own_name (G_BUS_TYPE_SYSTEM,
            "org.genivi.SimpleNodeStateMachine",
            G_BUS_NAME_OWNER_FLAGS_NONE,
            NULL,
            on_name_acquired,
            NULL,
            NULL,
            NULL);


    return retval;
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
        g_object_unref(pConnection);
        g_object_unref(pStateMachine);
    }

    return NsmErrorStatus_Ok;
}
