#include "ips/logger/log.hpp"

#include <iostream>

#include "details/consoleFormatter.hpp"
#include "details/dateFormatter.hpp"
#include "details/fileWriter.hpp"
#include "details/storage.hpp"
#include "details/streamWriter.hpp"

namespace ips::logger {

[[maybe_unused]] void init::file(Id id, const std::string& filename,
                                 Severity severity, Level maxLevel,
                                 const Seconds seconds) noexcept {
  details::Storage::instance().add(
      {id, severity,
       std::make_shared<details::FileWriter>(filename,
                                             std::chrono::seconds{seconds}),
       std::make_shared<details::DateFormatter>(), maxLevel});
}

[[maybe_unused]] void init::console(Severity severity,
                                    Level maxLevel) noexcept {
  details::Storage::instance().add(
      {kConsoleId, severity, std::make_shared<details::StreamWriter>(std::cout),
       std::make_shared<details::ConsoleFormatter>(), maxLevel});
}

[[maybe_unused]] void init::erase(const Id id) noexcept {
  details::Storage::instance().remove(id);
}

[[maybe_unused]] Recorder log(const Severity severity, const Level level,
                              const Id id,
                              const std::source_location location) noexcept {
  return Recorder{id, severity, level, location};
}

[[maybe_unused]] Recorder fatal(const Level level, const Id id,
                                const std::source_location location) noexcept {
  return log(Severity::kFatal, level, id, location);
}

[[maybe_unused]] Recorder error(const Level level, const Id id,
                                const std::source_location location) noexcept {
  return log(Severity::kError, level, id, location);
}

[[maybe_unused]] Recorder warning(
    const Level level, const Id id,
    const std::source_location location) noexcept {
  return log(Severity::kWarning, level, id, location);
}

[[maybe_unused]] Recorder info(const Level level, const Id id,
                               const std::source_location location) noexcept {
  return log(Severity::kInfo, level, id, location);
}

[[maybe_unused]] Recorder trace(const Level level, const Id id,
                                const std::source_location location) noexcept {
  return log(Severity::kTrace, level, id, location);
}

[[maybe_unused]] Recorder debug(const Level level, const Id id,
                                const std::source_location location) noexcept {
  return log(Severity::kDebug, level, id, location);
}

}  // namespace ips::logger