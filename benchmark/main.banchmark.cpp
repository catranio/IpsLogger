#include <benchmark/benchmark.h>

#include "logger.hpp"
#include "time_convertion.hpp"

int main(int argc, char** argv) {
  // ipslog file
  RegisterBenchmark("file/ipslog", logger::ipslogFile)
      ->Setup(logger::ipslogFileSetup)
      ->Teardown(logger::ipslogFileTeardown);
  RegisterBenchmark("file/ipslog", logger::ipslogFile)
      ->Setup(logger::ipslogFileSetup)
      ->Teardown(logger::ipslogFileTeardown)
      ->Threads(2);
  RegisterBenchmark("file/ipslog", logger::ipslogFile)
      ->Setup(logger::ipslogFileSetup)
      ->Teardown(logger::ipslogFileTeardown)
      ->Threads(4);
  RegisterBenchmark("file/ipslog", logger::ipslogFile)
      ->Setup(logger::ipslogFileSetup)
      ->Teardown(logger::ipslogFileTeardown)
      ->Threads(8);
  RegisterBenchmark("file/ipslog", logger::ipslogFile)
      ->Setup(logger::ipslogFileSetup)
      ->Teardown(logger::ipslogFileTeardown)
      ->Threads(18);

  // spdlog file
  RegisterBenchmark("file/spdlog", logger::spdlogFile)
      ->Setup(logger::spdlogFileSetup)
      ->Teardown(logger::spdlogFileTeardown);
  RegisterBenchmark("file/spdlog", logger::spdlogFile)
      ->Setup(logger::spdlogFileSetup)
      ->Teardown(logger::spdlogFileTeardown)
      ->Threads(2);
  RegisterBenchmark("file/spdlog", logger::spdlogFile)
      ->Setup(logger::spdlogFileSetup)
      ->Teardown(logger::spdlogFileTeardown)
      ->Threads(4);
  RegisterBenchmark("file/spdlog", logger::spdlogFile)
      ->Setup(logger::spdlogFileSetup)
      ->Teardown(logger::spdlogFileTeardown)
      ->Threads(8);
  RegisterBenchmark("file/spdlog", logger::spdlogFile)
      ->Setup(logger::spdlogFileSetup)
      ->Teardown(logger::spdlogFileTeardown)
      ->Threads(18);

  // helper
  RegisterBenchmark("details/tp2sec/hmdata",
        logger::details::hmdataTimePointToSeconds)
      ->Threads(1);
  RegisterBenchmark("details/tp2sec/chrono",
        logger::details::chronoTimePointToSeconds)
      ->Threads(1);
  RegisterBenchmark("details/tp2string/hmdate",
        logger::details::timepointToSting)
      ->Threads(1);
  RegisterBenchmark("details/tp2string-chahed/hmdate",
        logger::details::timepointToStingChahed)
      ->Threads(1);

  // initialize
  benchmark::Initialize(&argc, argv);
  benchmark::RunSpecifiedBenchmarks();
  benchmark::Shutdown();
}