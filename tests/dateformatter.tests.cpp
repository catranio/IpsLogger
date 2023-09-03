#include <doctest/doctest.h>
#include <fmt/chrono.h>
#include <fmt/format.h>

#include <details/dateFormatter.hpp>
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

  auto timestamp = rec.getTimestamp();
#if defined(__APPLE__)
  timestamp *= 1000; /* linux use nanoseconds for time_point */
#endif
  const auto &ns = std::chrono::nanoseconds{timestamp};
  const auto &mc = std::chrono::duration_cast<std::chrono::microseconds>(ns);
  const auto &tp = std::chrono::time_point<std::chrono::system_clock>(mc);
  auto expect = fmt::format("[{:%Y.%m.%d %H:%M:}{:%S}] {}({}): {}\n", tp, mc,
                            ips::logger::to_string(rec.getSeverity()),
                            rec.getLevel(), rec.getBuffer());
  CHECK(assert == expect);
}

TEST_SUITE_END();