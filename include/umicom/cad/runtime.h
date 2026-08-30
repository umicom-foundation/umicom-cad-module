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

UmiStatus umi_cad_runtime_init(
    UmiApplicationWorkspaceRuntime *out_runtime);
UmiStatus umi_cad_runtime_health(
    UmiApplicationCapabilityProbe probe,
    void *user_data,
    UmiApplicationRuntimeHealth *out_health);
const UmiApplicationExperienceDefinition *umi_cad_runtime_experience(void);

#ifdef __cplusplus
}
#endif

#endif
