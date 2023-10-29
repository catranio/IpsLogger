#include <benchmark/benchmark.h>

#include "logger.hpp"

int main(int argc, char** argv) {
  // ipslog console
  //  benchmark::RegisterBenchmark("console/ipslog", logger::ipslog_console);
  //  benchmark::RegisterBenchmark("console/ipslog", logger::ipslog_console)
  //      ->Threads(2);
  //  benchmark::RegisterBenchmark("console/ipslog", logger::ipslog_console)
  //      ->Threads(4);
  //  benchmark::RegisterBenchmark("console/ipslog", logger::ipslog_console)
  //      ->Threads(8);
  //
  //  // spdlog console
  //  benchmark::RegisterBenchmark("console/spdlog", logger::spdlog_console);
  //  benchmark::RegisterBenchmark("console/spdlog", logger::spdlog_console)
  //      ->Threads(2);
  //  benchmark::RegisterBenchmark("console/spdlog", logger::spdlog_console)
  //      ->Threads(4);
  //  benchmark::RegisterBenchmark("console/spdlog", logger::spdlog_console)
  //      ->Threads(8);

  // ipslog file
  benchmark::RegisterBenchmark("file/ipslog", logger::ipslog_file);
  benchmark::RegisterBenchmark("file/ipslog", logger::ipslog_file)->Threads(2);
  benchmark::RegisterBenchmark("file/ipslog", logger::ipslog_file)->Threads(4);
  benchmark::RegisterBenchmark("file/ipslog", logger::ipslog_file)->Threads(8);

  // spdlog file
  benchmark::RegisterBenchmark("file/spdlog", logger::spdlog_file);
  benchmark::RegisterBenchmark("file/spdlog", logger::spdlog_file)->Threads(2);
  benchmark::RegisterBenchmark("file/spdlog", logger::spdlog_file)->Threads(4);
  benchmark::RegisterBenchmark("file/spdlog", logger::spdlog_file)->Threads(8);

  // initialize
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}