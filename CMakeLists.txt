cmake_minimum_required(VERSION 3.24)
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
        ${LIBS_SOURCE_DIR}/Common/IpsCMakeModules/IpsCMakeModulesConfig.in
        ${LIBS_SOURCE_DIR}/Common/IpsCMakeModules/IpsCMakeModulesConfig.cmake
        INSTALL_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/lib/IpsCMakeModules/cmake)
set(IpsCMakeModules_DIR ${LIBS_SOURCE_DIR}/Common/IpsCMakeModules/)
find_package(IpsCMakeModules)

ips_init(${PROJECT_NAME} CXX 17)

# Dependencies
FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 9.1.0
        CONFIGURE_COMMAND "-DCMAKE_CXX_STANDARD=17"
        SOURCE_DIR ${LIBS_SOURCE_DIR}/common/fmt)
FetchContent_MakeAvailable(fmt)

ips_add_target(${PROJECT_NAME} STATIC
        HEADERS ${CMAKE_SOURCE_DIR}/include/*
        SOURCES ${CMAKE_SOURCE_DIR}/sources/*
        DEPENDS fmt)
