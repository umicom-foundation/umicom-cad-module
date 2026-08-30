/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: src/productisation_contribution.c
 *
 * PURPOSE:
 *   Bind product identity and executable evidence to canonical Framework
 *   application definitions without copying shared implementation.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/cad/productisation_contribution.h"

static const UmiProductApplicationAdoption ADOPTION = {
    sizeof(UmiProductApplicationAdoption),
    "cad",
    "org.umicom.cad",
    "Umicom CAD",
    "umicom-cad-console",
    UMI_PRODUCT_FRONTEND_FLAG_CONSOLE,
    1,
    1,
    1,
    1
};

const UmiProductApplicationAdoption *
umi_cad_productisation_contribution(void)
{
    return &ADOPTION;
}

UmiStatus umi_cad_productisation_snapshot(
    UmiProductApplicationAdoptionSnapshot *out_snapshot)
{
    return umi_product_application_adoption_snapshot(
        &ADOPTION, out_snapshot);
}

/* Start this product through the Framework-owned session command plane. */
UmiStatus umi_cad_product_session_init(
    UmiProductApplicationSession *out_session)
{
    return umi_product_application_session_init(
        &ADOPTION, out_session);
}
