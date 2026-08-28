/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: include/umicom/cad/workspace_commands.h
 *
 * PURPOSE:
 *   Expose product-facing layout, panel and context commands implemented by the Framework runtime.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/


#ifndef UMICOM_CAD_WORKSPACE_COMMANDS_H
#define UMICOM_CAD_WORKSPACE_COMMANDS_H

#include "umicom/cad/runtime.h"

#ifdef __cplusplus
extern "C" {
#endif

UmiStatus umi_cad_workspace_select_layout(
    UmiApplicationWorkspaceRuntime *runtime,
    const char *layout_id);
UmiStatus umi_cad_workspace_activate_panel(
    UmiApplicationWorkspaceRuntime *runtime,
    const char *panel_id);
UmiStatus umi_cad_workspace_set_context(
    UmiApplicationWorkspaceRuntime *runtime,
    const char *group_id,
    const char *value);
const UmiApplicationCommandSurface *umi_cad_workspace_commands(
    const UmiApplicationWorkspaceRuntime *runtime);

#ifdef __cplusplus
}
#endif

#endif
