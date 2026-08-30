/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: include/umicom/cad/application.h
 *
 * PURPOSE:
 *   Expose the thin application composition over Framework-owned experience metadata and services.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_CAD_APPLICATION_H
#define UMICOM_CAD_APPLICATION_H

#include "umicom/application/experience.h"
#include "umicom/application/experience_status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define UMI_CAD_MODULE_API_VERSION 1U

const char *umi_cad_application_id(void);

const UmiApplicationExperienceDefinition *
umi_cad_application_experience(void);

UmiStatus umi_cad_application_status(
    UmiApplicationExperienceStatus *out_status);

#ifdef __cplusplus
}
#endif

#endif
