#include <doctest/doctest.h>
#include <fmt/chrono.h>
#include <fmt/format.h>

#include <details/dateFormatter.hpp>
#include <details/utils.hpp>
#include <ips/logger/definitions.hpp>
#include <ips/logger/recorder.hpp>

TEST_SUITE_BEGIN("formatter");

TEST_CASE("dateformatter") {
  using namespace ips::logger;
  const auto severity = Severity::kTrace;
  const auto level = 2;
  const auto *message = "some message for logging.";

  const details::DateFormatter df;
  Recorder rec{"", severity, level};
  rec << message;
  auto assert = df.fmt(rec);

  std::string expect;
  expect.reserve(rec.getBuffer().size() + 32);
  fmt::format_to(std::back_inserter(expect), "[{}|{}] ",
                 details::utils::to_string(rec.getTimestamp()),
                 to_string(rec.getSeverity()));
  expect += rec.getBuffer() + "\n";

  CHECK(assert == expect);
}

TEST_SUITE_END();