/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: include/umicom/cad/productisation_contribution.h
 *
 * PURPOSE:
 *   Declare this thin module's adoption of Framework-owned application
 *   experience, components, layouts and productisation evidence.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#ifndef UMICOM_CAD_PRODUCTISATION_CONTRIBUTION_H
#define UMICOM_CAD_PRODUCTISATION_CONTRIBUTION_H

#include "umicom/application/productisation/session.h"

#ifdef __cplusplus
extern "C" {
#endif

const UmiProductApplicationAdoption *
umi_cad_productisation_contribution(void);
UmiStatus umi_cad_productisation_snapshot(
    UmiProductApplicationAdoptionSnapshot *out_snapshot);
UmiStatus umi_cad_product_session_init(
    UmiProductApplicationSession *out_session);

#ifdef __cplusplus
}
#endif

#endif
