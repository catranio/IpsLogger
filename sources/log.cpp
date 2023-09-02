#include "ips/logger/log.hpp"

#include <iostream>

#include "details/consoleFormatter.hpp"
#include "details/dateFormatter.hpp"
#include "details/fileWriter.hpp"
#include "details/storage.hpp"
#include "details/streamWriter.hpp"

namespace ips::logger {

[[maybe_unused]] void ips::logger::init::file(const id_t& id,
                                              const std::string& filename,
                                              Severity severity,
                                              level_t maxLevel,
                                              seconds_t seconds) noexcept {
  details::Storage::instance().add(
      details::Logger{id, severity,
                      std::make_unique<details::FileWriter>(
                          filename, std::chrono::seconds{seconds}),
                      std::make_unique<details::DateFormatter>(), maxLevel});
}

[[maybe_unused]] void ips::logger::init::console(Severity severity,
                                                 level_t maxLevel) noexcept {
  details::Storage::instance().add(details::Logger{
      kConsoleId, severity, std::make_unique<details::StreamWriter>(std::cout),
      std::make_unique<details::ConsoleFormatter>(), maxLevel});
}

[[maybe_unused]] void ips::logger::init::erase(const id_t& id) noexcept {
  details::Storage::instance().remove(id);
}

[[maybe_unused]] Recorder log(Severity severity, level_t level,
                              const id_t& id) noexcept {
  return Recorder{id, severity, level};
}

[[maybe_unused]] Recorder fatal(level_t level, const id_t& id) noexcept {
  return log(Severity::kFatal, level, id);
}

[[maybe_unused]] Recorder error(level_t level, const id_t& id) noexcept {
  return log(Severity::kError, level, id);
}

[[maybe_unused]] Recorder warning(level_t level, const id_t& id) noexcept {
  return log(Severity::kWarning, level, id);
}

[[maybe_unused]] Recorder info(level_t level, const id_t& id) noexcept {
  return log(Severity::kInfo, level, id);
}

[[maybe_unused]] Recorder trace(level_t level, const id_t& id) noexcept {
  return log(Severity::kTrace, level, id);
}

[[maybe_unused]] Recorder debug(level_t level, const id_t& id) noexcept {
  return log(Severity::kDebug, level, id);
}

}  // namespace ips::logger