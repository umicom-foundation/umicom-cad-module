/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: tests/test_workspace_commands.c
 *
 * PURPOSE:
 *   Verify product commands forward to the canonical Framework workspace runtime.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


#include <assert.h>

#include "umicom/cad/workspace_commands.h"

int main(void)
{
    UmiApplicationWorkspaceRuntime runtime;
    const UmiApplicationExperienceDefinition *experience =
        umi_cad_runtime_experience();
    const UmiApplicationCommandSurface *commands;
    assert(experience != NULL);
    assert(umi_cad_runtime_init(&runtime) == UMI_STATUS_OK);
    assert(umi_cad_workspace_select_layout(
               &runtime, experience->default_layout_id) == UMI_STATUS_OK);
    assert(umi_cad_workspace_activate_panel(
               &runtime, experience->panels[0].panel_id) == UMI_STATUS_OK);
    commands = umi_cad_workspace_commands(&runtime);
    assert(commands != NULL);
    assert(umi_application_command_surface_find(
               commands, UMI_APPLICATION_COMMAND_SELECT_LAYOUT,
               experience->default_layout_id) != NULL);
    assert(umi_cad_workspace_commands(NULL) == NULL);
    return 0;
}
