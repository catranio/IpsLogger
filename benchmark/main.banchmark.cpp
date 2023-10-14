#include <benchmark/benchmark.h>

#include "logger.hpp"

int main(int argc, char** argv) {
  benchmark::RegisterBenchmark("logger", logger::one_log);
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}