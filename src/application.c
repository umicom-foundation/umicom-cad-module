/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: src/application.c
 *
 * PURPOSE:
 *   Bind the product identity to the canonical Framework application-experience catalogue.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "umicom/cad/application.h"

#include "umicom/application/experience_catalogue.h"

const char *umi_cad_application_id(void)
{
    return "org.umicom.cad";
}

const UmiApplicationExperienceDefinition *
umi_cad_application_experience(void)
{
    return umi_application_experience_catalogue_find(
        umi_cad_application_id());
}

UmiStatus umi_cad_application_status(
    UmiApplicationExperienceStatus *out_status)
{
    const UmiApplicationExperienceDefinition *definition =
        umi_cad_application_experience();
    if (definition == NULL) return UMI_STATUS_NOT_FOUND;
    return umi_application_experience_status(definition, out_status);
}
