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

int main(void)
{
    const UmiProductApplicationAdoption *adoption =
        umi_cad_productisation_contribution();
    UmiProductApplicationAdoptionSnapshot snapshot;
    UmiProductApplicationSession session;
    UmiProductApplicationSessionSnapshot session_snapshot;
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
    return 0;
}
