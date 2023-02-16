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
    using id_t = unsigned;

    constexpr static level_t kMaxLevelDefault = 10;
    constexpr static level_t kLevelDefault = 3;
    constexpr static id_t kIdDefault = 0;
}

#endif /* IPSLOGGER_DEFINITIONS_HPP */
