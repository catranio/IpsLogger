#include <ips/logger/ditails/dateFormatter.hpp>
#include <ips/logger/recorder.hpp>

#include <string>

#include <fmt/format.h>

using namespace ips::logger;

std::string DateFormatter::fmt(const Recorder &recorder) noexcept {
    return fmt::format("{:%H:%M:%S}", recorder.getTimestamp());
}