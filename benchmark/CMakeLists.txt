set(BENCHMARK_ENABLE_TESTING OFF)
ips_fetch(benchmark GIT_REPOSITORY https://github.com/google/benchmark.git GIT_TAG v1.8.3)
ips_fetch(spdlog GIT_REPOSITORY https://github.com/gabime/spdlog.git GIT_TAG v1.12.0)
ips_fetch(hw_date GIT_REPOSITORY https://github.com/HowardHinnant/date.git GIT_TAG v3.0.1)
ips_fetch(fmt GIT_REPOSITORY https://github.com/fmtlib/fmt.git GIT_TAG 10.1.1)

ips_add_target(${PROJECT_NAME}.benchmark EXECUTABLE
        SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*
        DEPENDS ${PROJECT_NAMESPACE}::${PROJECT_NAME} benchmark::benchmark spdlog::spdlog date::date fmt::fmt)