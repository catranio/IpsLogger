#ifndef IPSLOGGER_LOGGER_HPP
#define IPSLOGGER_LOGGER_HPP

#include <benchmark/benchmark.h>
#include <spdlog/async.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <fstream>
#include <iostream>
#include <ips/logger/log.hpp>

namespace logger {
[[maybe_unused]] static void ipslog_console(benchmark::State& state) {
  if (state.thread_index() == 0) {
    ipslog::init::console(ips::logger::Severity::kAll);
  }
  for ([[maybe_unused]] auto _ : state) {
    ipslog::info() << "some logger string #" << 1;
  }
}

[[maybe_unused]] static void ipslog_file(benchmark::State& state) {
  if (state.thread_index() == 0) {
    ipslog::init::file("trace", "ipslog.log", ips::logger::Severity::kAll);
  }
  for ([[maybe_unused]] auto _ : state) {
    ipslog::info() << "some logger string #" << 1;
  }
}

// spdlog
[[maybe_unused]] static void spdlog_console(benchmark::State& state) {
  if (!spdlog::get("console") && state.thread_index() == 0) {
    spdlog::stdout_color_mt("console");
  }
  for ([[maybe_unused]] auto _ : state) {
    spdlog::get("console")->info("some logger string #{}", 1);
  }
}

[[maybe_unused]] static void spdlog_file(benchmark::State& state) {
  if (!spdlog::get("basic_logger") && state.thread_index() == 0) {
    spdlog::basic_logger_mt("basic_logger", "spdlog.log");
  }
  for ([[maybe_unused]] auto _ : state) {
    spdlog::get("basic_logger")->info("some logger string #{}", 1);
  }
}

}  // namespace logger

#endif /* IPSLOGGER_LOGGER_HPP */
