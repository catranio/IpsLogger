#include "ips/logger/recorder.hpp"

#include <fmt/format.h>

#include <exception>
#include <source_location>
#include <string>
#include <utility>

#include "details/storage.hpp"

constexpr static std::size_t kBufferSize = 512;

namespace ips::logger {
Recorder::Recorder(Id id, const Severity severity, const Level level,
                   const std::source_location location)
    : severity_(severity),
      level_(level),
      id_(std::move(id)),
      location_(location) {
  buffer_.reserve(kBufferSize);
  timestamp_ = std::chrono::system_clock::now();
}

Recorder::~Recorder() { details::Storage::instance().write(*this); }

Recorder& Recorder::operator<<(char value) noexcept {
  fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
  return *this;
}

Recorder& Recorder::operator<<(std::string_view value) noexcept {
  fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
  return *this;
}

Recorder& Recorder::operator<<(float value) noexcept {
  fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
  return *this;
}

Recorder& Recorder::operator<<(double value) noexcept {
  fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{:g}"), value);
  return *this;
}

Recorder& Recorder::operator<<(long double value) noexcept {
  fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{:g}"), value);
  return *this;
}

Recorder& Recorder::operator<<(unsigned long long value) noexcept {
  fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
  return *this;
}

Recorder& Recorder::operator<<(long long value) noexcept {
  fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value);
  return *this;
}

Recorder& Recorder::operator<<(const bool value) noexcept {
  fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"),
                 value ? "true" : "false");
  return *this;
}

Recorder& Recorder::operator<<(const std::exception& value) noexcept {
  fmt::format_to(std::back_inserter(buffer_), FMT_STRING("{}"), value.what());
  return *this;
}

Recorder::Timstamp Recorder::getTimestamp() const noexcept {
  return timestamp_;
}

Severity Recorder::getSeverity() const noexcept { return severity_; }

Level Recorder::getLevel() const noexcept { return level_; }

std::string_view Recorder::getId() const noexcept { return id_; }

std::source_location Recorder::getSourceLocation() const noexcept {
  return location_;
}

const Recorder::Buffer& Recorder::getBuffer() const noexcept { return buffer_; }
}  // namespace ips::logger