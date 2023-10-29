#include "dateFormatter.hpp"

#include <fmt/chrono.h>
#include <fmt/format.h>

#include <ips/logger/definitions.hpp>
#include <ips/logger/recorder.hpp>

namespace ips::logger::details {

std::string DateFormatter::fmt(const Recorder& recorder) const noexcept {
  auto timestamp = recorder.getTimestamp();
#if defined(__APPLE__)
  timestamp *= 1000; /* linux use nanoseconds for time_point*/
#endif
  const auto& ns = std::chrono::nanoseconds{timestamp};
  const auto& mc = std::chrono::duration_cast<std::chrono::microseconds>(ns);
  const auto& tp = std::chrono::time_point<std::chrono::system_clock>(mc);
  return fmt::format("[{:%Y.%m.%d %H:%M:}{:%S}] {}: {}\n", tp, mc,
                     ips::logger::to_string(recorder.getSeverity()),
                     recorder.getBuffer());
}

}  // namespace ips::logger::details
