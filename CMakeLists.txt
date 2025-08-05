cmake_minimum_required(VERSION 3.15)

project(digestpp VERSION 1.0.0
    DESCRIPTION "C++11 header-only message digest library"
    HOMEPAGE_URL "https://github.com/kerukuro/digestpp"
    LANGUAGES CXX)

include(GNUInstallDirs)

add_library(digestpp INTERFACE)
add_library(digestpp::digestpp ALIAS digestpp)

set(VIRTUAL_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/_generated_include")

file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/algorithm"
    "${CMAKE_CURRENT_SOURCE_DIR}/detail"
    DESTINATION "${VIRTUAL_INCLUDE_DIR}/digestpp"
)
file(COPY
    "${CMAKE_CURRENT_SOURCE_DIR}/digestpp.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/hasher.hpp"
    DESTINATION "${VIRTUAL_INCLUDE_DIR}/digestpp"
)

target_include_directories(digestpp INTERFACE
    $<BUILD_INTERFACE:${VIRTUAL_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_compile_features(digestpp INTERFACE cxx_std_11)

install(
    DIRECTORY algorithm detail
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/digestpp"
)
install(
    FILES digestpp.hpp hasher.hpp
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/digestpp"
)

install(TARGETS digestpp EXPORT digestppTargets)

install(EXPORT digestppTargets
    FILE digestppTargets.cmake
    NAMESPACE digestpp::
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

export(TARGETS digestpp
    FILE "${PROJECT_BINARY_DIR}/digestppTargets.cmake"
    NAMESPACE digestpp::
)

include(CMakePackageConfigHelpers)

set(CONFIG_TEMPLATE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cmake/${PROJECT_NAME}Config.cmake.in")
if(NOT EXISTS "${CONFIG_TEMPLATE_FILE}")
    file(WRITE "${CONFIG_TEMPLATE_FILE}"
        "@PACKAGE_INIT@\n"
        "if(NOT TARGET digestpp::digestpp)\n"
        "  include(\"\${CMAKE_CURRENT_LIST_DIR}/digestppTargets.cmake\")\n"
        "endif()\n"
    )
endif()

configure_package_config_file(
    "${CONFIG_TEMPLATE_FILE}"
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}"
)

