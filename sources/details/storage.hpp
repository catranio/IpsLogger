#ifndef IPSLOGGER_DETAILS_STORAGE_HPP
#define IPSLOGGER_DETAILS_STORAGE_HPP

#include <ips/logger/recorder.hpp>
#include <mutex>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "logger.hpp"

namespace ips::logger::details {
class Storage final {
 private:
  Storage() = default;
  ~Storage() = default;

 public:
  Storage(const Storage&) = delete;
  Storage(Storage&&) = delete;
  Storage& operator=(const Storage&) = delete;
  Storage&& operator=(Storage&&) = delete;

  static Storage& instance() noexcept;
  void add(Logger&& logger) noexcept;
  void remove(const id_t& id) noexcept;
  void write(const Recorder& recorder) noexcept;

 private:
  static bool isWrite(const Recorder& recorder, const Logger& logger) noexcept;

  using storage_t = std::unordered_map<std::string_view, Logger>;
  using mutex_t = std::mutex;
  storage_t storage_;
  mutex_t mutex_;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_STORAGE_HPP */
