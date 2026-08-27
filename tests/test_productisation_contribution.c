/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: tests/test_productisation_contribution.c
 *
 * PURPOSE:
 *   Verify this module remains a thin, runnable and testable composition of
 *   canonical Framework product surfaces.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/
#include <assert.h>
#include <string.h>

#include "umicom/cad/productisation_contribution.h"

int main(void)
{
    const UmiProductApplicationAdoption *adoption =
        umi_cad_productisation_contribution();
    UmiProductApplicationAdoptionSnapshot snapshot;
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
    assert(snapshot.missing_surface_count == 0U);
    assert(snapshot.covered_surface_count == snapshot.panel_count);
    assert(snapshot.runnable);
    assert(snapshot.acceptance_ready);
    return 0;
}
