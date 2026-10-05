/*-----------------------------------------------------------------------------
 * Umicom CAD Module
 * File: tests/test_context_review.c
 * PURPOSE: Exercise this product adapter against the shared context review contract.
 * AUTHOR AND ORGANISATION: Sammy Hegab, Umicom Foundation
 * LICENCE: MIT
 *---------------------------------------------------------------------------*/
#include "umicom/cad/workspace_commands.h"
#include "umicom/application/experience_catalogue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Keep checks active in release configurations as well as debug builds. */
#define CHECK(condition) do { if (!(condition)) { \
    fprintf(stderr, "line %d: %s\n", __LINE__, #condition); return 1; } } while (0)

int main(int argc, char **argv)
{
    const char *scenario = argc > 1 ? argv[1] : "publication";
    UmiApplicationWorkspaceRuntime *runtime = calloc(1U, sizeof(*runtime));
    UmiApplicationContextReview *review = NULL;
    UmiApplicationContextReviewSummary summary;
    UmiApplicationContextReviewRow row;
    UmiApplicationContextChange changes[2] = {
        { UMI_APPLICATION_CONTEXT_SET, "linked.primary", "first" },
        { UMI_APPLICATION_CONTEXT_SET, "linked.secondary", "second" }
    };
    UmiCommandRegistry *commands = NULL;
    UmiUiWorkbench *workbench = NULL;
    UmiUiContextSnapshot snapshot;
    CHECK(runtime != NULL);
    CHECK(umi_cad_runtime_init(runtime) == UMI_STATUS_OK);
    CHECK(umi_command_registry_create(&commands) == UMI_STATUS_OK);
    CHECK(umi_ui_workbench_create("context.review", commands, &workbench) == UMI_STATUS_OK);
    CHECK(umi_application_workspace_runtime_bind_workbench(runtime, workbench) == UMI_STATUS_OK);
    CHECK(umi_ui_context_set_integer(umi_ui_workbench_context(workbench),
        "unrelated", 42) == UMI_STATUS_OK);
    /* Existing typed UI values must be visible in the copied review rows. */
    if (strcmp(scenario, "divergent_ui") == 0)
        CHECK(umi_ui_context_set_integer(umi_ui_workbench_context(workbench),
            "linked.primary", 99) == UMI_STATUS_OK);
    CHECK(umi_cad_workspace_context_review(runtime, changes, 2U, &review) == UMI_STATUS_OK);
    CHECK(runtime->contexts.entry_count == 0U);
    CHECK(umi_application_context_review_summary(review, &summary) == UMI_STATUS_OK);
    CHECK(summary.added_count == 2U && summary.has_workbench && !summary.applied);
    CHECK(umi_application_context_review_row(review, 0U, &row) == UMI_STATUS_OK);
    CHECK(!row.existed && strcmp(row.change.value, "first") == 0);
    if (strcmp(scenario, "divergent_ui") == 0) {
        CHECK(summary.ui_difference_count == 1U && row.ui_existed && !row.cache_matches_ui);
        CHECK(row.ui_previous.kind == UMI_UI_CONTEXT_INTEGER && row.ui_previous.integer_value == 99);
    } else CHECK(summary.ui_difference_count == 0U);

    if (strcmp(scenario, "stale") == 0) {
        /* An external UI update must invalidate the proposal without changing
         * either linked group or advancing the application's revision. */
        CHECK(umi_ui_context_set_integer(umi_ui_workbench_context(workbench),
            "unrelated", 43) == UMI_STATUS_OK);
        CHECK(umi_cad_workspace_context_apply(runtime, review) == UMI_STATUS_INVALID_STATE);
        CHECK(runtime->contexts.entry_count == 0U && runtime->contexts.revision == 0U);
        CHECK(umi_ui_context_get(umi_ui_workbench_context(workbench),
            "linked.primary", &snapshot) == UMI_STATUS_NOT_FOUND);
    } else if (strcmp(scenario, "foreign") == 0) {
        /* Identity checks must run at the product boundary, not merely accept
         * any structurally valid workspace from another application. */
        const UmiApplicationExperienceDefinition *original = runtime->session.experience;
        runtime->session.experience = umi_application_experience_catalogue_find(
            strcmp(original->application_id, "org.umicom.trader") == 0
                ? "org.umicom.studio" : "org.umicom.trader");
        CHECK(runtime->session.experience != NULL && runtime->session.experience != original);
        CHECK(umi_cad_workspace_context_apply(runtime, review) == UMI_STATUS_INVALID_ARGUMENT);
        CHECK(umi_cad_workspace_clear_context(runtime, "linked.primary") == UMI_STATUS_INVALID_ARGUMENT);
        CHECK(umi_cad_workspace_context_review(runtime, changes, 2U, &review) == UMI_STATUS_INVALID_ARGUMENT);
        runtime->session.experience = original;
        CHECK(runtime->contexts.entry_count == 0U);
    } else {
        CHECK(strcmp(scenario, "publication") == 0 || strcmp(scenario, "clear") == 0 || strcmp(scenario, "divergent_ui") == 0);
        CHECK(umi_cad_workspace_context_apply(runtime, review) == UMI_STATUS_OK);
        CHECK(runtime->contexts.entry_count == 2U && runtime->contexts.revision == 1U);
        CHECK(umi_application_context_review_summary(review, &summary) == UMI_STATUS_OK && summary.applied);
        CHECK(umi_cad_workspace_context_apply(runtime, review) == UMI_STATUS_INVALID_STATE);
        CHECK(umi_ui_context_get(umi_ui_workbench_context(workbench),
            "linked.primary", &snapshot) == UMI_STATUS_OK);
        CHECK(snapshot.kind == UMI_UI_CONTEXT_STRING && strcmp(snapshot.string_value, "first") == 0);
        if (strcmp(scenario, "clear") == 0) {
            CHECK(umi_cad_workspace_clear_context(runtime, "linked.primary") == UMI_STATUS_OK);
            CHECK(umi_application_context_binding_get(&runtime->contexts, "linked.primary") == NULL);
            CHECK(umi_ui_context_get(umi_ui_workbench_context(workbench),
                "linked.primary", &snapshot) == UMI_STATUS_NOT_FOUND);
            CHECK(umi_cad_workspace_clear_context(runtime, "linked.primary") == UMI_STATUS_NOT_FOUND);
            CHECK(runtime->contexts.entry_count == 1U && runtime->contexts.revision == 2U);
        }
        CHECK(umi_ui_context_get(umi_ui_workbench_context(workbench), "unrelated", &snapshot) == UMI_STATUS_OK);
        CHECK(snapshot.kind == UMI_UI_CONTEXT_INTEGER && snapshot.integer_value == 42);
    }
    umi_application_context_review_destroy(review);
    umi_application_workspace_runtime_unbind_workbench(runtime);
    umi_ui_workbench_destroy(workbench);
    umi_command_registry_destroy(commands);
    free(runtime);
    return 0;
}
