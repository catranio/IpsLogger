cmake_minimum_required(VERSION 3.2)
project(IpsLogger)
set(LIBS_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs)

include(FetchContent)
FetchContent_Declare(IpsCMakeModules
        GIT_REPOSITORY https://github.com/catranio/IpsCMakeModules.git
        SOURCE_DIR ${LIBS_SOURCE_DIR}/common/IpsCMakeModules)
FetchContent_MakeAvailable(IpsCMakeModules)
find_package(IpsCMakeModules PATHS ${IpsCMakeModules_CONFIG_DIR})

ips_init(${PROJECT_NAME} CXX 17)

# Dependencies
FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 9.1.0
        SOURCE_DIR ${LIBS_SOURCE_DIR}/fmt/)
set(CMAKE_MESSAGE_LOG_LEVEL WARNING)
FetchContent_MakeAvailable(fmt)
unset(CMAKE_MESSAGE_LOG_LEVEL)

ips_add_target(${PROJECT_NAME} STATIC
        HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*
        DEPENDS fmt)

if (BUILD_TESTS)
    FetchContent_Declare(doctest
            GIT_REPOSITORY https://github.com/doctest/doctest.git
            GIT_TAG v2.4.11
            SOURCE_DIR ${LIBS_SOURCE_DIR}/doctest/)
    FetchContent_MakeAvailable(doctest)

    ips_add_target(${PROJECT_NAME}.tests EXECUTABLE
            HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*
            SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/tests/*
            DEPENDS ${PROJECT_NAME} doctest::doctest)

    enable_testing()
    add_test(NAME recorder COMMAND ${PROJECT_NAME}.tests -ts="recorder")
endif ()