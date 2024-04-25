#ifndef IPS_LOGGER_LOG_HPP
#define IPS_LOGGER_LOG_HPP

#ifndef IPS_LOGGER_ERASE
#define IPS_LOGGER_ERASE false
#include <source_location>
#endif /* IPS_LOGGER_ERASE */

#define ipslog            \
  if (IPS_LOGGER_ERASE) { \
  } else                  \
    ips::logger
#define ipslogc(ENABLE_LOG_CONDITION)                \
  if (IPS_LOGGER_ERASE && !(ENABLE_LOG_CONDITION)) { \
  } else                                             \
    ips::logger

#include <ips/logger/definitions.hpp>
#include <ips/logger/formatter.hpp>
#include <ips/logger/recorder.hpp>
#include <ips/logger/version.hpp>
#include <ips/logger/writer.hpp>

namespace ips::logger::init {
[[maybe_unused]] void file(Id id, const std::string& filename,
                           Severity severity, Level maxLevel = kMaxLevelDefault,
                           Seconds seconds = kTimeRotateDefault) noexcept;

[[maybe_unused]] void console(Severity severity,
                              Level maxLevel = kMaxLevelDefault) noexcept;

[[maybe_unused]] void erase(Id id) noexcept;
}  // namespace ips::logger::init

namespace ips::logger {
[[maybe_unused]] Recorder log(
    Severity severity, Level level = kLevelDefault, Id id = kConsoleId,
    std::source_location location = std::source_location::current()) noexcept;

[[maybe_unused]] Recorder fatal(
    Level level = kLevelDefault, Id id = kConsoleId,
    std::source_location location = std::source_location::current()) noexcept;

[[maybe_unused]] Recorder error(
    Level level = kLevelDefault, Id id = kConsoleId,
    std::source_location location = std::source_location::current()) noexcept;

[[maybe_unused]] Recorder warning(
    Level level = kLevelDefault, Id id = kConsoleId,
    std::source_location location = std::source_location::current()) noexcept;

[[maybe_unused]] Recorder info(
    Level level = kLevelDefault, Id id = kConsoleId,
    std::source_location location = std::source_location::current()) noexcept;

[[maybe_unused]] Recorder trace(
    Level level = kLevelDefault, Id id = kConsoleId,
    std::source_location location = std::source_location::current()) noexcept;

[[maybe_unused]] Recorder debug(
    Level level = kLevelDefault, Id id = kConsoleId,
    std::source_location location = std::source_location::current()) noexcept;

}  // namespace ips::logger

/* generate ipslog custom function */
#define ipslog_gen_func(name, postfix, severity)                  \
  namespace ips::logger {                                         \
  inline Recorder name##_##postfix(Level level = kLevelDefault) { \
    return Recorder{#name, Severity::severity, level};            \
  };                                                              \
  };

#define ipslog_gen_funcs(name)              \
  ipslog_gen_func(name, fatal, kFatal);     \
  ipslog_gen_func(name, error, kError);     \
  ipslog_gen_func(name, warning, kWarning); \
  ipslog_gen_func(name, info, kInfo);       \
  ipslog_gen_func(name, trace, kTrace);     \
  ipslog_gen_func(name, debug, kDebug);

#endif /* IPS_LOGGER_LOG_HPP */
