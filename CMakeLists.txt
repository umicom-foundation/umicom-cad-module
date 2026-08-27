#-----------------------------------------------------------------------------
# Umicom CAD Module
# File: CMakeLists.txt
#
# PURPOSE:
#   Build a thin C23 product composition over Framework-owned application
#   experience, runtime and workbench contracts.
#
# Created by: Sammy Hegab
# Organisation: Umicom Foundation
# Licence: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)

project(
    CadModule
    VERSION 0.1.0
    DESCRIPTION "Thin Umicom CAD composition over Umicom Framework"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(UMICOM_CAD_BUILD_CONSOLE
       "Build the native Umicom CAD verification console"
       ON)

include(CTest)
include(GNUInstallDirs)

if(NOT TARGET Umicom::Framework)
    find_package(UmicomFramework CONFIG REQUIRED)
endif()

if(NOT TARGET Umicom::application)
    message(FATAL_ERROR
        "Umicom CAD requires Framework target Umicom::application")
endif()

if(NOT COMMAND umicom_apply_warnings)
    function(umicom_apply_warnings target)
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        else()
            target_compile_options(${target} PRIVATE
                -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endfunction()
endif()

if(NOT COMMAND umicom_apply_sanitizers)
    function(umicom_apply_sanitizers target)
    endfunction()
endif()

add_library(umicom_cad_module STATIC
    src/application.c
    src/workspace.c
)
add_library(Umicom::cad_module ALIAS umicom_cad_module)

target_include_directories(umicom_cad_module PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(umicom_cad_module PUBLIC
    Umicom::Framework
    Umicom::application
)
umicom_apply_warnings(umicom_cad_module)
umicom_apply_sanitizers(umicom_cad_module)

if(UMICOM_CAD_BUILD_CONSOLE)
    add_executable(umicom-cad-console
        src/console/main.c)
    target_link_libraries(umicom-cad-console PRIVATE Umicom::cad_module)
    umicom_apply_warnings(umicom-cad-console)
    umicom_apply_sanitizers(umicom-cad-console)
endif()

if(BUILD_TESTING)
    add_executable(cad-application-test
        tests/test_application.c)
    target_link_libraries(cad-application-test PRIVATE Umicom::cad_module)
    umicom_apply_warnings(cad-application-test)
    umicom_apply_sanitizers(cad-application-test)
    add_test(NAME cad.module.application
             COMMAND cad-application-test)

    add_executable(cad-workspace-test
        tests/test_workspace.c)
    target_link_libraries(cad-workspace-test PRIVATE Umicom::cad_module)
    umicom_apply_warnings(cad-workspace-test)
    umicom_apply_sanitizers(cad-workspace-test)
    add_test(NAME cad.module.workspace
             COMMAND cad-workspace-test)
endif()

install(TARGETS umicom_cad_module
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(TARGET umicom-cad-console)
    install(TARGETS umicom-cad-console
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES application.umicom.yaml
    DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/cad)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    install(FILES LICENSE
        DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/cad)
endif()

message(STATUS "Umicom CAD Module version: ${PROJECT_VERSION}")
message(STATUS "Umicom CAD uses Framework-owned application experience")

include(
    "${CMAKE_CURRENT_SOURCE_DIR}/../../framework/cmake/UmicomApplicationProductisationContribution.cmake")
umicom_add_application_productisation_contribution(
    NAME "cad"
    TARGET umicom_cad_productisation
    SOURCE "src/productisation_contribution.c"
    TEST_SOURCE "tests/test_productisation_contribution.c")
