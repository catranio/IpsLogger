#ifndef IPS_LOGGER_LOG_HPP
#define IPS_LOGGER_LOG_HPP

#ifndef IPS_LOGGER_ENABLE
#define IPS_LOGGER_ENABLE true
#endif /* IPS_LOGGER_ENABLE */

#define ipslog if (!IPS_LOGGER_ENABLE) {} else ips::logger
#define ipslogc(ENABLE_LOG_CONDITION) if (!IPS_LOGGER_ENABLE && !IPS_LOGGER_ENABLE) {} else ips::logger

#include <ips/logger/definitions.hpp>
#include <ips/logger/formatter.hpp>
#include <ips/logger/writer.hpp>
#include <ips/logger/recorder.hpp>

namespace ips::logger
{
    [[maybe_unused]] void init(const id_t& id, const std::string& filename, Severity severity,
                     level_t maxLevel = kMaxLevelDefault) noexcept;
	[[maybe_unused]] void remove(const id_t& id) noexcept;

    inline Recorder log(const id_t& id, Severity severity, level_t level = kLevelDefault) noexcept;
    [[maybe_unused]] Recorder fatal(const id_t& id, level_t level = kLevelDefault) noexcept;
    [[maybe_unused]] Recorder error(const id_t& id, level_t level = kLevelDefault) noexcept;
    [[maybe_unused]] Recorder warning(const id_t& id, level_t level = kLevelDefault) noexcept;
    [[maybe_unused]] Recorder info(const id_t& id, level_t level = kLevelDefault) noexcept;
    [[maybe_unused]] Recorder trace(const id_t& id, level_t level = kLevelDefault) noexcept;
    [[maybe_unused]] Recorder debug(const id_t& id, level_t level = kLevelDefault) noexcept;

}

#endif /* IPS_LOGGER_LOG_HPP */
