#ifndef IPSLOGGER_LOGGER_HPP
#define IPSLOGGER_LOGGER_HPP

#include <benchmark/benchmark.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/spdlog.h>

#include <fstream>
#include <iostream>
#include <ips/logger/log.hpp>

namespace logger {
// ipslog
constexpr auto kIpslogFilename = "ipslog.log";
constexpr auto kIpslogBasicId = "ipslog";
constexpr auto kSpdlogFilename = "spdlog.log";
constexpr auto kSpdlogBasicId = "basic_logger";

[[maybe_unused]] static void ipslogFileSetup(const benchmark::State&) {
  ipslog::init::file(kIpslogBasicId, kIpslogFilename,
                     ips::logger::Severity::kAll);
}
[[maybe_unused]] static void ipslogFileTeardown(const benchmark::State&) {
  std::remove(kIpslogFilename);
}

[[maybe_unused]] static void ipslogFile(benchmark::State& state) {
  for ([[maybe_unused]] auto _ : state) {
    ipslog::log(ips::logger::Severity::kInfo, 1, kIpslogBasicId)
        << "some logger string #" << 1;
  }
}

// spdlog
[[maybe_unused]] static void spdlogFileSetup(const benchmark::State&) {
  spdlog::basic_logger_mt(kSpdlogBasicId, kSpdlogFilename);
}
[[maybe_unused]] static void spdlogFileTeardown(const benchmark::State&) {
  spdlog::drop(kSpdlogBasicId);
  std::remove(kSpdlogFilename);
}

[[maybe_unused]] static void spdlogFile(benchmark::State& state) {
  for ([[maybe_unused]] auto _ : state) {
    spdlog::get(kSpdlogBasicId)->info("some logger string #{}", 1);
  }
}

}  // namespace logger

#endif /* IPSLOGGER_LOGGER_HPP */
