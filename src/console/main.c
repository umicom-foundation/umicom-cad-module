/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: src/console/main.c
 *
 * PURPOSE:
 *   Provide a native verification frontend for the thin product composition.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include <stdio.h>

#include "umicom/cad/application.h"
#include "umicom/cad/workspace.h"

/*
 * Start this command or application, report setup failures, and return a process exit code
 * to the operating system.
 */
int main(void)
{
    UmiApplicationExperienceStatus status;
    const UmiApplicationExperienceDefinition *definition =
        umi_cad_application_experience();
    const UmiExperienceLayoutDefinition *layout =
        umi_cad_workspace_default();
    const UmiExperienceFeatureDefinition *next =
        umi_cad_workspace_next_feature();

    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (definition == NULL ||
        umi_cad_application_status(&status) != UMI_STATUS_OK ||
        layout == NULL) {
        fputs("Umicom CAD: Framework experience unavailable\n", stderr);
        return 1;
    }

    printf("%s\n", definition->display_name);
    printf("application: %s\n", definition->application_id);
    printf("default layout: %s\n", layout->title);
    printf("panels: %zu\n", status.panel_count);
    printf("layouts: %zu\n", status.layout_count);
    printf("features: %zu\n", status.feature_count);
    printf("readiness: %u%%\n", status.readiness_percent);
    /*
     * Protect caller-owned memory by checking that required state is available before it is
     * used.
     */
    if (next != NULL)
        printf("next: %s [%s]\n", next->title,
               umi_experience_priority_text(next->priority));
    return 0;
}
