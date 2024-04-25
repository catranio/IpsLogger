#include "storage.hpp"

#include <mutex>

namespace ips::logger::details {

Storage& Storage::instance() noexcept {
  static Storage storage;
  return storage;
}

void Storage::add(Logger&& logger) noexcept {
  const auto id = logger.getId();
  const std::scoped_lock lock{mutex_};
  if (const auto it = storage_.find(id); it == storage_.end()) {
    storage_.try_emplace(std::string{id}, std::move(logger));
  }
}

void Storage::remove(const Id id) noexcept {
  const std::scoped_lock lock{mutex_};
  if (const auto it = storage_.find(id); it != storage_.end()) {
    storage_.erase(it);
  }
}

void Storage::write(const Recorder& recorder) noexcept {
  const auto id = recorder.getId();
  std::shared_lock lock{mutex_};
  const auto cit = storage_.find(id);
  if (cit == storage_.end() || !isWrite(recorder, cit->second)) {
    return;
  }

  const auto logger = cit->second;
  lock.unlock();
  std::string buffer;
  buffer.reserve(250);
  logger.getFormatter().fmt(recorder, buffer);
  logger.getWriter().write(buffer);
}

bool Storage::isWrite(const Recorder& recorder, const Logger& logger) noexcept {
  if (recorder.getLevel() >= logger.getMaxLevel()) {
    return false;
  }

  if (logger.getSeverityEqualMode() == Logger::SeverityEqualMode::kStrong) {
    return recorder.getSeverity() == logger.getSeverity();
  }

  return recorder.getSeverity() <= logger.getSeverity();
}

}  // namespace ips::logger::details
