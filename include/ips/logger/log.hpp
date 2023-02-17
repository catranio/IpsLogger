#ifndef IPS_LOGGER_LOG_HPP
#define IPS_LOGGER_LOG_HPP

#ifndef IPS_LOGGER_ENABLE
#define IPS_LOGGER_ENABLE true
#endif /* IPS_LOGGER_ENABLE */

#define ipslog(IPS_LOGGER_ENABLE) if (IPS_LOGGER_ENABLE) else ips::logger
#define ipslogc(ENABLE_LOG_CONDITION) if (IPS_LOGGER_ENABLE && IPS_LOGGER_ENABLE) else ips::logger

#include <ips/logger/definitions.hpp>
#include <ips/logger/formatter.hpp>
#include <ips/logger/writer.hpp>
#include <ips/logger/recorder.hpp>

namespace ips::logger
{
    [[maybe_unused]] inline void init(const std::string& filename, Severity severity,
                     level_t level = kMaxLevelDefault, id_t id = kIdDefault) noexcept;

    [[maybe_unused]] inline void uninit(id_t id) noexcept;

    inline Recorder log(Severity severity, level_t level = kLevelDefault, id_t id = kIdDefault) noexcept;
    [[maybe_unused]] inline Recorder fatal(level_t level = kLevelDefault, id_t id = kIdDefault) noexcept;
    [[maybe_unused]] inline Recorder error(level_t level = kLevelDefault, id_t id = kIdDefault) noexcept;
    [[maybe_unused]] inline Recorder warning(level_t level = kLevelDefault, id_t id = kIdDefault) noexcept;
    [[maybe_unused]] inline Recorder info(level_t level = kLevelDefault, id_t id = kIdDefault) noexcept;
    [[maybe_unused]] inline Recorder trace(level_t level = kLevelDefault, id_t id = kIdDefault) noexcept;
    [[maybe_unused]] inline Recorder debug(level_t level = kLevelDefault, id_t id = kIdDefault) noexcept;

}

#endif /* IPS_LOGGER_LOG_HPP */
