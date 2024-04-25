cmake_minimum_required(VERSION 3.25)
project(logger)
set(PROJECT_NAMESPACE ips)

add_link_options(-lstdc++ -lm)

include(FetchContent)
FetchContent_Declare(IpsCMakeModules
        GIT_REPOSITORY https://github.com/catranio/IpsCMakeModules.git)
FetchContent_MakeAvailable(IpsCMakeModules)

ips_init(CXX 20)

# Dependencies
ips_fetch(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 10.1.1)
ips_fetch(hw_date GIT_REPOSITORY https://github.com/HowardHinnant/date.git GIT_TAG v3.0.1)

ips_add_target(${PROJECT_NAMESPACE}::${PROJECT_NAME} STATIC
        HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/sources/*
        DEPENDS fmt::fmt date::date)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

if (BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif ()

if (BUILD_PLAYGROUND)
    add_subdirectory(playground)
endif ()