/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: tests/test_application.c
 *
 * PURPOSE:
 *   Verify the product resolves only Framework-owned experience metadata.
 *
 * Created by: Sammy Hegab
 * Organisation: Umicom Foundation
 * Licence: MIT
 *---------------------------------------------------------------------------*/

#include <assert.h>

#include "umicom/cad/application.h"

int main(void)
{
    UmiApplicationExperienceStatus status;
    const UmiApplicationExperienceDefinition *definition =
        umi_cad_application_experience();

    assert(definition != NULL);
    assert(umi_application_experience_validate(definition) == UMI_STATUS_OK);
    assert(umi_cad_application_status(&status) == UMI_STATUS_OK);
    assert(status.feature_count == definition->feature_count);
    assert(status.panel_count == definition->panel_count);
    return 0;
}
