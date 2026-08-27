/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: tests/test_workspace.c
 *
 * PURPOSE:
 *   Verify the module exposes Framework-owned layouts without duplicating workbench logic.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#include <assert.h>

#include "umicom/cad/workspace.h"

int main(void)
{
    const UmiExperienceLayoutDefinition *layout =
        umi_cad_workspace_default();
    assert(umi_cad_workspace_layout_count() > 0U);
    assert(layout != NULL);
    assert(layout->panel_count > 0U);
    assert(umi_cad_workspace_layout_at(0U) != NULL);
    return 0;
}
