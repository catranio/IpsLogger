#ifndef IPSLOGGER_LOGGER_HPP
#define IPSLOGGER_LOGGER_HPP

#include <benchmark/benchmark.h>

#include <iostream>
#include <ips/logger/log.hpp>

namespace logger {
[[maybe_unused]] static void one_log(benchmark::State& state) {
  using enum ips::logger::Severity;
  ipslog::init::console(kAll);
  for ([[maybe_unused]] auto _ : state) {
    ipslog::info() << "some logger string #" << 1;
  }
}
}  // namespace logger

#endif /* IPSLOGGER_LOGGER_HPP */
