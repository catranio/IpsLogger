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

  struct string_hash {
    using hash_type = std::hash<std::string_view>;
    using is_transparent [[maybe_unused]] = void;

    std::size_t operator()(const char* str) const { return hash_type{}(str); }
    std::size_t operator()(std::string_view str) const {
      return hash_type{}(str);
    }
    std::size_t operator()(const std::string& str) const {
      return hash_type{}(str);
    }
  };
  using storage_t =
      std::unordered_map<std::string, Logger, string_hash, std::equal_to<>>;
  using mutex_t = std::mutex;
  storage_t storage_;
  mutex_t mutex_;
};
}  // namespace ips::logger::details

#endif /* IPSLOGGER_DETAILS_STORAGE_HPP */
