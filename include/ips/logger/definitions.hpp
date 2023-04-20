#ifndef IPSLOGGER_DEFINITIONS_HPP
#define IPSLOGGER_DEFINITIONS_HPP

namespace ips::logger
{
    enum class Severity {
        NONE,
        FATAL,
        ERROR,
        WARNING,
        INFO,
        TRACE,
        DEBUG,
        ALL,
    };

    using level_t = unsigned;

    constexpr static level_t kMaxLevelDefault = 10;
    constexpr static level_t kLevelDefault = 3;

    constexpr const char* to_string(Severity severity) noexcept {
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
}

#endif /* IPSLOGGER_DEFINITIONS_HPP */
