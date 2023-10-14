set(BENCHMARK_ENABLE_TESTING OFF)
ips_fetch(benchmark GIT_REPOSITORY https://github.com/google/benchmark.git GIT_TAG v1.8.3)

ips_add_target(${PROJECT_NAME}.benchmark EXECUTABLE
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*
        DEPENDS ${PROJECT_NAMESPACE}::${PROJECT_NAME} benchmark::benchmark)