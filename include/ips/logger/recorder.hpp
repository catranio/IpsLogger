#ifndef IPSLOGGER_RECORDER_HPP
#define IPSLOGGER_RECORDER_HPP

#include <chrono>
#include <concepts>
#include <iostream>
#include <source_location>
#include <string>

#include "definitions.hpp"

namespace ips::logger {
class Recorder final {
 public:
  using Timstamp = std::chrono::time_point<std::chrono::system_clock>;
  using Buffer = std::string;

  Recorder(Id id, Severity severity, Level level,
           std::source_location location = {});
  ~Recorder();

  Recorder(const Recorder&) = delete;
  Recorder(Recorder&&) = delete;
  Recorder& operator=(const Recorder&) = delete;
  Recorder&& operator=(Recorder&&) = delete;

  Recorder& operator<<(
      const std::convertible_to<std::string_view> auto& value) {
    return *this << std::string_view{value};
  }

  Recorder& operator<<(const std::signed_integral auto& value) {
    using LongLong = long long;
    return *this << LongLong{value};
  }

  Recorder& operator<<(const std::unsigned_integral auto& value) {
    using UnsigndeLongLong = unsigned long long;
    return *this << UnsigndeLongLong{value};
  }

  Recorder& operator<<(const std::derived_from<std::exception> auto& value) {
    return *this << static_cast<const std::exception&>(value);
  }

  template <class T>
  Recorder& operator<<(const T&) {
    static_assert(
        !sizeof(T),
        "Please implement logging for your type: "
        "ips::logger::Recorder& operator<<(ips::logger::Recorder& recorder, "
        "const T& value)");
    return *this;
  }

  Recorder& operator<<(char value) noexcept;
  Recorder& operator<<(std::string_view value) noexcept;
  Recorder& operator<<(float value) noexcept;
  Recorder& operator<<(double value) noexcept;
  Recorder& operator<<(long double value) noexcept;
  Recorder& operator<<(unsigned long long value) noexcept;
  Recorder& operator<<(long long value) noexcept;
  Recorder& operator<<(bool value) noexcept;
  Recorder& operator<<(const std::exception& value) noexcept;

  [[nodiscard]] Timstamp getTimestamp() const noexcept;
  [[nodiscard]] Severity getSeverity() const noexcept;
  [[nodiscard]] Level getLevel() const noexcept;
  [[nodiscard]] std::string_view getId() const noexcept;
  [[nodiscard]] std::source_location getSourceLocation() const noexcept;
  [[nodiscard]] const Buffer& getBuffer() const noexcept;

 private:
  const Severity severity_;
  const Level level_;
  const Id id_;
  Buffer buffer_;
  Timstamp timestamp_;
  std::source_location location_;
};
}  // namespace ips::logger

#endif /* IPSLOGGER_RECORDER_HPP */
