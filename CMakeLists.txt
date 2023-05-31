cmake_minimum_required(VERSION 3.11)
project(IpsLogger)

include(FetchContent)
FetchContent_Declare(IpsCMakeModules
        GIT_REPOSITORY https://github.com/catranio/IpsCMakeModules.git)
FetchContent_MakeAvailable(IpsCMakeModules)
find_package(IpsCMakeModules PATHS ${IpsCMakeModules_CONFIG_DIR})

ips_init(${PROJECT_NAME} CXX 17)

#Dependencies
ips_fetch(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 10.0.0)

ips_add_target(${PROJECT_NAME} STATIC
        HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*
        DEPENDS fmt)
ips_pedantic_error(${PROJECT_NAME})

if (${PROJECT_NAME}_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()