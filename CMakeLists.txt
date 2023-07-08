cmake_minimum_required(VERSION 3.11)
project(Logger)
set(PROJECT_NAMESPACE IPS)

include(FetchContent)
FetchContent_Declare(IpsCMakeModules
        GIT_REPOSITORY https://github.com/catranio/IpsCMakeModules.git)
FetchContent_MakeAvailable(IpsCMakeModules)

ips_init(CXX 17)

#Dependencies
ips_fetch(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 10.0.0)

ips_add_target(${PROJECT_NAMESPACE}::${PROJECT_NAME} STATIC
        HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*
        DEPENDS fmt::fmt)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()