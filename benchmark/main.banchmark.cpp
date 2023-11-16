#include <benchmark/benchmark.h>

#include <ranges>
#include <thread>

#include "logger.hpp"

int main(int argc, char** argv) {
  // ipslog file
  benchmark::RegisterBenchmark("file/ipslog", logger::ipslog_file)
      ->Setup(logger::ipslog_file_setup)
      ->Teardown(logger::ipslog_file_teardown);
  benchmark::RegisterBenchmark("file/ipslog", logger::ipslog_file)
      ->Setup(logger::ipslog_file_setup)
      ->Teardown(logger::ipslog_file_teardown)
      ->Threads(2);
  benchmark::RegisterBenchmark("file/ipslog", logger::ipslog_file)
      ->Setup(logger::ipslog_file_setup)
      ->Teardown(logger::ipslog_file_teardown)
      ->Threads(4);
  benchmark::RegisterBenchmark("file/ipslog", logger::ipslog_file)
      ->Setup(logger::ipslog_file_setup)
      ->Teardown(logger::ipslog_file_teardown)
      ->Threads(8);

  // spdlog file
  benchmark::RegisterBenchmark("file/spdlog", logger::spdlog_file)
      ->Setup(logger::spdlog_file_setup)
      ->Teardown(logger::spdlog_file_teardown);
  benchmark::RegisterBenchmark("file/spdlog", logger::spdlog_file)
      ->Setup(logger::spdlog_file_setup)
      ->Teardown(logger::spdlog_file_teardown)
      ->Threads(2);
  benchmark::RegisterBenchmark("file/spdlog", logger::spdlog_file)
      ->Setup(logger::spdlog_file_setup)
      ->Teardown(logger::spdlog_file_teardown)
      ->Threads(4);
  benchmark::RegisterBenchmark("file/spdlog", logger::spdlog_file)
      ->Setup(logger::spdlog_file_setup)
      ->Teardown(logger::spdlog_file_teardown)
      ->Threads(8);

  // initialize
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}