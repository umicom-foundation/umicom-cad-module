/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: src/workspace.c
 *
 * PURPOSE:
 *   Project canonical Framework layouts and next-feature planning through the thin application boundary.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/cad/workspace.h"

#include "umicom/cad/application.h"
#include "umicom/application/experience_plan.h"

size_t umi_cad_workspace_layout_count(void)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_cad_application_experience();
    return definition != NULL ? definition->layout_count : 0U;
}

const UmiExperienceLayoutDefinition *umi_cad_workspace_layout_at(
    size_t index)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_cad_application_experience();
    return definition != NULL && index < definition->layout_count
        ? &definition->layouts[index] : NULL;
}

const UmiExperienceLayoutDefinition *umi_cad_workspace_default(void)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_cad_application_experience();
    return definition != NULL
        ? umi_application_experience_layout_find(
            definition, definition->default_layout_id)
        : NULL;
}

const UmiExperienceFeatureDefinition *umi_cad_workspace_next_feature(
    void)
{
    return umi_application_experience_next_feature(
        umi_cad_application_experience());
}
