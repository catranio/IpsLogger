#ifndef IPS_LOGGER_LOG_HPP
#define IPS_LOGGER_LOG_HPP

#ifndef IPS_LOGGER_ERASE
#define IPS_LOGGER_ERASE false
#endif /* IPS_LOGGER_ERASE */

#define ipslog            \
  if (IPS_LOGGER_ERASE) { \
  } else                  \
    ips::logger
#define ipslogc(ENABLE_LOG_CONDITION)              \
  if (IPS_LOGGER_ERASE && !ENABLE_LOG_CONDITION) { \
  } else                                           \
    ips::logger

#include <ips/logger/definitions.hpp>
#include <ips/logger/formatter.hpp>
#include <ips/logger/recorder.hpp>
#include <ips/logger/version.hpp>
#include <ips/logger/writer.hpp>

namespace ips::logger::init {
[[maybe_unused]] void file(const id_t& id, const std::string& filename,
                           Severity severity,
                           level_t maxLevel = kMaxLevelDefault,
                           unsigned seconds = kTimeRotateDefault) noexcept;

[[maybe_unused]] void console(Severity severity,
                              level_t maxLevel = kMaxLevelDefault) noexcept;
}  // namespace ips::logger::init

namespace ips::logger {
inline Recorder log(Severity severity, level_t level = kLevelDefault,
                    const id_t& id = kConsoleId) noexcept;

[[maybe_unused]] Recorder fatal(level_t level = kLevelDefault,
                                const id_t& id = kConsoleId) noexcept;

[[maybe_unused]] Recorder error(level_t level = kLevelDefault,
                                const id_t& id = kConsoleId) noexcept;

[[maybe_unused]] Recorder warning(level_t level = kLevelDefault,
                                  const id_t& id = kConsoleId) noexcept;

[[maybe_unused]] Recorder info(level_t level = kLevelDefault,
                               const id_t& id = kConsoleId) noexcept;

[[maybe_unused]] Recorder trace(level_t level = kLevelDefault,
                                const id_t& id = kConsoleId) noexcept;

[[maybe_unused]] Recorder debug(level_t level = kLevelDefault,
                                const id_t& id = kConsoleId) noexcept;

}  // namespace ips::logger

#endif /* IPS_LOGGER_LOG_HPP */
