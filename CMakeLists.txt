cmake_minimum_required(VERSION 3.2)
project(IpsLogger)
set(LIBS_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs)

include(FetchContent)
# Fetching ips-cmake-modules
FetchContent_Declare(ips-cmake-modules
        GIT_REPOSITORY https://github.com/catranio/IpsCMakeModules.git
        SOURCE_DIR ${LIBS_SOURCE_DIR}/common/IpsCMakeModules)
FetchContent_Populate(ips-cmake-modules)
include(CMakePackageConfigHelpers)
configure_package_config_file(
        ${LIBS_SOURCE_DIR}/common/IpsCMakeModules/IpsCMakeModulesConfig.in
        ${LIBS_SOURCE_DIR}/common/IpsCMakeModules/IpsCMakeModulesConfig.cmake
        INSTALL_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib/IpsCMakeModules/cmake)
set(IpsCMakeModules_DIR ${LIBS_SOURCE_DIR}/common/IpsCMakeModules/)
find_package(IpsCMakeModules)

ips_init(${PROJECT_NAME} CXX 17)

# Dependencies
FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 9.1.0
        SOURCE_DIR ${LIBS_SOURCE_DIR}/fmt/)
FetchContent_MakeAvailable(fmt)

ips_add_target(${PROJECT_NAME} STATIC
        HEADERS ${CMAKE_SOURCE_DIR}/include/*
        SOURCES ${CMAKE_SOURCE_DIR}/sources/*
        DEPENDS fmt)

if (BUILD_TESTS)
    FetchContent_Declare(doctest
            GIT_REPOSITORY https://github.com/doctest/doctest.git
            GIT_TAG v2.4.9
            SOURCE_DIR ${LIBS_SOURCE_DIR}/doctest/)
    FetchContent_MakeAvailable(doctest)

    ips_add_target(${PROJECT_NAME}.tests EXECUTABLE
            HEADERS ${CMAKE_SOURCE_DIR}/include/*
            SOURCES ${CMAKE_SOURCE_DIR}/tests/*
            DEPENDS ${PROJECT_NAME} doctest::doctest)
endif ()