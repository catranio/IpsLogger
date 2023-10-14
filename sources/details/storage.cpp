#include "storage.hpp"

namespace ips::logger::details {

Storage& Storage::instance() noexcept {
  static Storage storage;
  return storage;
}

void Storage::add(Logger&& logger) noexcept {
  const auto id = logger.getId();
  const std::scoped_lock lock{mutex_};
  auto it = storage_.find(id);
  if (it == storage_.end()) {
    storage_.try_emplace(id, std::move(logger));
  }
}

void Storage::remove(const id_t& id) noexcept {
  const std::scoped_lock lock{mutex_};
  auto it = storage_.find(id);
  if (it != storage_.end()) {
    storage_.erase(it);
  }
}

void Storage::write(const Recorder& recorder) noexcept {
  const auto id = recorder.getId();
  const std::scoped_lock lock{mutex_};
  auto it = storage_.find(id);
  if (it == storage_.end() || !isWrite(recorder, it->second)) {
    return;
  }

  const auto& logger = it->second;
  const auto msg = logger.getFormatter().fmt(recorder);
  logger.getWriter().write(msg);
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
