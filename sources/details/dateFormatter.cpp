#include "dateFormatter.hpp"
#include <ips/logger/recorder.hpp>
#include <ips/logger/definitions.hpp>

#include <fmt/format.h>
#include <fmt/chrono.h>

using namespace ips::logger::details;

std::string DateFormatter::fmt(const Recorder &recorder) const noexcept {
    auto timestamp = recorder.getTimestamp();
#if defined(__APPLE__)
    timestamp *= 1000; /* linux use nanoseconds for time_point*/
#endif
    auto ns = std::chrono::nanoseconds{timestamp};
    auto mc = std::chrono::duration_cast<std::chrono::microseconds>(ns);
    auto sec = std::chrono::duration_cast<std::chrono::seconds>(ns);
    auto tp = std::chrono::time_point<std::chrono::system_clock>(mc);
    return fmt::format("[{:%Y.%m.%d %H:%M:}{:%S}] {}({}): {}\n",
                       tp, mc - sec,
                       ips::logger::to_string(recorder.getSeverity()),
                       recorder.getLevel(),
                       recorder.getBuffer());
}