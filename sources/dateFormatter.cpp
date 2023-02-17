#include <ips/logger/ditails/dateFormatter.hpp>
#include <ips/logger/recorder.hpp>

#include <fmt/format.h>
#include <fmt/chrono.h>

using namespace ips::logger::ditails;

std::string DateFormatter::fmt(const Recorder &recorder) noexcept {
    return fmt::format("{[:%Y.:%m.:%d :%H:%M:%S] {1}({2}) {3}\n}",
                       recorder.getTimestamp(),
                       to_string(recorder.getSeverity()),
                       recorder.getLevel(),
                       recorder.getBuffer());
}

constexpr std::string_view DateFormatter::to_string(Severity severity) noexcept {
    switch (severity) {
        case Severity::FATAL: return "fatal";
        case Severity::ERROR: return "error";
        case Severity::WARNING: return "warning";
        case Severity::INFO: return "info";
        case Severity::TRACE: return "trace";
        case Severity::DEBUG: return "debug";
        case Severity::ALL: return "all";
        case Severity::NONE:
        default: return "";
    }
}