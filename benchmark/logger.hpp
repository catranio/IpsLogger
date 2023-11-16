#ifndef IPSLOGGER_LOGGER_HPP
#define IPSLOGGER_LOGGER_HPP

#include <benchmark/benchmark.h>
#include <fcntl.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <ips/logger/log.hpp>

namespace logger {
// ipslog
[[maybe_unused]] static void ipslog_file_setup(const benchmark::State&) {
  ipslog::init::file("trace", "ipslog.log", ips::logger::Severity::kAll);
}
[[maybe_unused]] static void ipslog_file_teardown(const benchmark::State&) {
  std::remove("ipslog.log");
}

[[maybe_unused]] static void ipslog_file(benchmark::State& state) {
  for ([[maybe_unused]] auto _ : state) {
    ipslog::info(1, "trace") << "some logger string #" << 1;
  }
}

// spdlog
[[maybe_unused]] static void spdlog_file_setup(const benchmark::State&) {
  spdlog::basic_logger_mt("basic_logger", "spdlog.log");
}
[[maybe_unused]] static void spdlog_file_teardown(const benchmark::State&) {
  spdlog::drop("basic_logger");
  std::remove("spdlog.log");
}

[[maybe_unused]] static void spdlog_file(benchmark::State& state) {
  for ([[maybe_unused]] auto _ : state) {
    spdlog::get("basic_logger")->info("some logger string #{}", 1);
  }
}

}  // namespace logger

#endif /* IPSLOGGER_LOGGER_HPP */
