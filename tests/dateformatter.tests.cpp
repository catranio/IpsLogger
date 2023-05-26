#include <doctest/doctest.h>
#include <fmt/chrono.h>
#include <fmt/format.h>

#include <details/dateFormatter.hpp>
#include <ips/logger/definitions.hpp>
#include <ips/logger/recorder.hpp>

using namespace ::ips::logger;

TEST_SUITE_BEGIN("formatter");

constexpr std::string_view to_string(Severity severity) noexcept {
  switch (severity) {
    case Severity::FATAL:
      return "fatal";
    case Severity::ERROR:
      return "error";
    case Severity::WARNING:
      return "warning";
    case Severity::INFO:
      return "info";
    case Severity::TRACE:
      return "trace";
    case Severity::DEBUG:
      return "debug";
    case Severity::ALL:
      return "all";
    case Severity::NONE:
    default:
      return "";
  }
}

TEST_CASE("dateformatter") {
  const auto severity = Severity::TRACE;
  const auto level = 2;
  const auto message = "some message for logging.";

  details::DateFormatter df;
  Recorder rec{"", severity, level};
  rec << message;
  auto assert = df.fmt(rec);

  auto timestamp = rec.getTimestamp();
#if defined(__APPLE__)
  timestamp *= 1000; /* linux use nanoseconds for time_point*/
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