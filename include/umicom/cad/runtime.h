/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: include/umicom/cad/runtime.h
 *
 * PURPOSE:
 *   Bind the thin product to the Framework-owned application workspace runtime without duplicating services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_CAD_RUNTIME_H
#define UMICOM_CAD_RUNTIME_H

#include "umicom/application/runtime/runtime.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Initialise cad runtime from caller-provided values so later operations receive a known
 * state.
 */
UmiStatus umi_cad_runtime_init(
    UmiApplicationWorkspaceRuntime *out_runtime);
/**
 * Provide the cad runtime health operation used by this module and its client
 * applications.
 */
UmiStatus umi_cad_runtime_health(
    UmiApplicationCapabilityProbe probe,
    void *user_data,
    UmiApplicationRuntimeHealth *out_health);
/**
 * Provide the cad runtime experience operation used by this module and its client
 * applications.
 */
const UmiApplicationExperienceDefinition *umi_cad_runtime_experience(void);

#ifdef __cplusplus
}
#endif

#endif
