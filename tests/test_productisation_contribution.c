/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: tests/test_productisation_contribution.c
 *
 * PURPOSE:
 *   Verify this module remains a thin, runnable and testable composition of
 *   canonical Framework product surfaces.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include <assert.h>
#include <string.h>

#include "umicom/cad/productisation_contribution.h"
#include "umicom/application/productisation/workspace_guide_portfolio.h"

/*
 * Start this command or application, report setup failures, and return a process exit code
 * to the operating system.
 */
int main(void)
{
    const UmiProductApplicationAdoption *adoption =
        umi_cad_productisation_contribution();
    UmiProductApplicationAdoptionSnapshot snapshot;
    UmiProductApplicationSession session;
    UmiProductApplicationSessionSnapshot session_snapshot;
    UmiProductWorkspaceGuide workspace_guide;
    const UmiProductWorkspaceGuideChoice *recommended_workspace;
    UmiProductAdoptionRegistry adoption_registry;
    UmiProductWorkspaceGuidePortfolio guide_portfolio;
    const UmiProductWorkspaceGuideSummary *portfolio_summary;
    UmiProductApplicationSessionCommand command = {
        sizeof(UmiProductApplicationSessionCommand),
        UMI_PRODUCT_SESSION_REFRESH_READINESS,
        NULL,
        NULL,
        false
    };
    assert(adoption != NULL);
    assert(strcmp(adoption->application_id, "org.umicom.cad") == 0);
    assert(umi_product_application_adoption_validate(adoption) ==
           UMI_STATUS_OK);
    assert(umi_cad_productisation_snapshot(&snapshot) ==
           UMI_STATUS_OK);
    assert(snapshot.canonical_experience_available);
    assert(snapshot.feature_count > 0U);
    assert(snapshot.panel_count > 0U);
    assert(snapshot.layout_count > 0U);
    assert(snapshot.projected_layout_count == snapshot.layout_count);
    assert(snapshot.projected_window_count >= snapshot.panel_count);
    assert(snapshot.default_layout_window_count > 0U);
    assert(snapshot.layout_runtime_ready);
    assert(snapshot.layout_projection_complete);
    assert(snapshot.missing_surface_count == 0U);
    assert(snapshot.covered_surface_count == snapshot.panel_count);
    assert(snapshot.runnable);
    assert(snapshot.acceptance_ready);
    assert(umi_cad_product_session_init(&session) ==
           UMI_STATUS_OK);
    assert(umi_product_application_session_execute(
        &session, &command) == UMI_STATUS_OK);
    assert(umi_product_application_session_snapshot(
        &session, &session_snapshot) == UMI_STATUS_OK);
    assert(strcmp(session_snapshot.application_id,
                  adoption->application_id) == 0);
    assert(session_snapshot.command_count == 1U);
    assert(session_snapshot.successful_command_count == 1U);
    assert(session_snapshot.failed_command_count == 0U);
    assert(session_snapshot.readiness_percent <= 100U);
    assert(session_snapshot.runnable);
    assert(session_snapshot.acceptance_ready);
    assert(umi_cad_product_workspace_guide(&workspace_guide) ==
           UMI_STATUS_OK);
    assert(umi_product_workspace_guide_validate(&workspace_guide) ==
           UMI_STATUS_OK);
    assert(workspace_guide.choice_count == snapshot.layout_count);
    assert(workspace_guide.total_panel_placements ==
           snapshot.projected_window_count);
    assert(workspace_guide.readiness_percent <= 100U);
    recommended_workspace =
        umi_product_workspace_guide_recommended(&workspace_guide);
    assert(recommended_workspace != NULL);
    assert(recommended_workspace->default_layout);
    assert(recommended_workspace->panel_count ==
           snapshot.default_layout_window_count);
    /* Prove this thin product can participate in a suite launcher portfolio. */
    umi_product_adoption_registry_init(&adoption_registry);
    assert(umi_product_adoption_registry_register(
        &adoption_registry, adoption) == UMI_STATUS_OK);
    assert(umi_product_workspace_guide_portfolio_build(
        &adoption_registry, &guide_portfolio) == UMI_STATUS_OK);
    assert(guide_portfolio.application_count == 1U);
    portfolio_summary = umi_product_workspace_guide_portfolio_find(
        &guide_portfolio, adoption->application_id);
    assert(portfolio_summary != NULL);
    assert(portfolio_summary->layout_choice_count ==
           workspace_guide.choice_count);
    assert(strcmp(portfolio_summary->recommended_layout_id,
                  workspace_guide.recommended_layout_id) == 0);
    return 0;
}
